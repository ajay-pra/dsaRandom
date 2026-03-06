// No need to require fetch in Node 18+ as it is global
const path = require('path');
require('dotenv').config();

const GITHUB_OWNER = process.env.GITHUB_OWNER || 'ajay-pra';
const GITHUB_REPO = process.env.GITHUB_REPO || 'dsaRandom';
const GITHUB_TOKEN = process.env.GITHUB_TOKEN; // Optional but recommended
const BRANCH = process.env.GITHUB_BRANCH || 'main';

console.log(`GitHub Config: Owner=${GITHUB_OWNER}, Repo=${GITHUB_REPO}, Branch=${BRANCH}`);

const CACHE_TTL = 5 * 60 * 1000; // 5 minutes
let treeCache = null;
let lastCacheTime = 0;

// Validation for required env vars in serverless
if (!process.env.GITHUB_OWNER || !process.env.GITHUB_REPO) {
    console.error('CRITICAL: GITHUB_OWNER or GITHUB_REPO is missing from environment variables!');
}

/**
 * Fetches the recursive file tree from GitHub with caching.
 */
async function getGithubTree() {
    console.log(`Fetching tree for ${GITHUB_OWNER}/${GITHUB_REPO} on branch ${BRANCH}...`);
    const now = Date.now();
    if (treeCache && (now - lastCacheTime < CACHE_TTL)) {
        return treeCache;
    }

    const url = `https://api.github.com/repos/${GITHUB_OWNER}/${GITHUB_REPO}/git/trees/${BRANCH}?recursive=1`;
    const headers = { 'Accept': 'application/vnd.github.v3+json' };
    if (GITHUB_TOKEN && GITHUB_TOKEN !== 'your-github-token-optional') {
        headers['Authorization'] = `token ${GITHUB_TOKEN}`;
    }

    const response = await fetch(url, { headers });
    if (!response.ok) {
        if (response.status === 403) throw new Error('GitHub API Rate Limit exceeded. Please add a GITHUB_TOKEN to .env');
        throw new Error(`GitHub API error: ${response.statusText}`);
    }

    const data = await response.json();
    treeCache = data.tree;
    lastCacheTime = now;
    return treeCache;
}

/**
 * Filters the tree for .cpp files and groups them into a structure for the UI.
 */
async function getGithubFolderStructure() {
    const tree = await getGithubTree();
    const root = { name: GITHUB_REPO, path: '', type: 'folder', children: [] };

    // Helper to find/create folder in our custom structure
    const getContainer = (parts) => {
        let current = root;
        let cumulativePath = '';
        for (const part of parts) {
            cumulativePath = cumulativePath ? `${cumulativePath}/${part}` : part;
            let child = current.children.find(c => c.name === part && c.type === 'folder');
            if (!child) {
                child = { name: part, path: cumulativePath, type: 'folder', children: [] };
                current.children.push(child);
            }
            current = child;
        }
        return current;
    };

    for (const item of tree) {
        if (item.type === 'tree') {
            getContainer(item.path.split('/'));
        }
    }

    // Sort children alphabetically
    const sortTree = (node) => {
        node.children.sort((a, b) => a.name.localeCompare(b.name));
        node.children.forEach(sortTree);
    };
    sortTree(root);

    return root;
}

/**
 * Gets all .cpp file paths.
 */
async function getAllCppPaths(subFolder = '') {
    const tree = await getGithubTree();
    return tree
        .filter(item => item.type === 'blob' && item.path.endsWith('.cpp'))
        .map(item => item.path)
        .filter(p => !subFolder || p === subFolder || p.startsWith(subFolder + '/'));
}

/**
 * Fetches file content from GitHub Raw.
 */
async function getFileContent(filePath) {
    const url = `https://raw.githubusercontent.com/${GITHUB_OWNER}/${GITHUB_REPO}/${BRANCH}/${filePath}`;
    const response = await fetch(url);
    if (!response.ok) throw new Error(`Failed to fetch file content: ${response.statusText}`);
    return await response.text();
}

/**
 * Fetches tracker.json from GitHub or returns default if not found.
 */
async function getTrackerFromGithub() {
    const url = `https://api.github.com/repos/${GITHUB_OWNER}/${GITHUB_REPO}/contents/tracker.json?ref=${BRANCH}`;
    const headers = { 'Accept': 'application/vnd.github.v3+json' };
    if (GITHUB_TOKEN) headers['Authorization'] = `token ${GITHUB_TOKEN}`;

    try {
        const response = await fetch(url, { headers });
        if (response.status === 404) return { sentEmails: [], manualRequests: [], solved: [], sha: null };

        const data = await response.json();
        const content = Buffer.from(data.content, 'base64').toString('utf-8');
        return { ...JSON.parse(content), sha: data.sha };
    } catch (err) {
        console.error('Error fetching tracker from GitHub:', err.message);
        return { sentEmails: [], manualRequests: [], solved: [], sha: null };
    }
}

/**
 * Updates tracker.json on GitHub.
 */
async function updateTrackerInGithub(tracker) {
    if (!GITHUB_TOKEN) throw new Error('GITHUB_TOKEN is required to update tracker on Netlify');

    const url = `https://api.github.com/repos/${GITHUB_OWNER}/${GITHUB_REPO}/contents/tracker.json`;
    const { sha, ...cleanTracker } = tracker; // Don't save the sha inside the file

    const body = {
        message: 'Update tracker.json [automated]',
        content: Buffer.from(JSON.stringify(cleanTracker, null, 2)).toString('base64'),
        branch: BRANCH
    };
    if (sha) body.sha = sha;

    const headers = {
        'Accept': 'application/vnd.github.v3+json',
        'Authorization': `token ${GITHUB_TOKEN}`,
        'Content-Type': 'application/json'
    };

    const response = await fetch(url, {
        method: 'PUT',
        headers,
        body: JSON.stringify(body)
    });

    if (!response.ok) {
        const errData = await response.json();
        throw new Error(`Failed to update tracker at ${url}: ${errData.message}`);
    }
}

module.exports = {
    getGithubFolderStructure,
    getAllCppPaths,
    getFileContent,
    getTrackerFromGithub,
    updateTrackerInGithub
};
