const express = require('express');
const serverless = require('serverless-http');
const path = require('path');
const {
    getGithubFolderStructure,
    getAllCppPaths,
    getFileContent,
    getTrackerFromGithub,
    updateTrackerInGithub
} = require('../../githubService');

const app = express();
app.use(express.json());

app.get('/api/folder-structure', async (req, res) => {
    try {
        const structure = await getGithubFolderStructure();
        res.json(structure);
    } catch (err) {
        res.status(500).json({ error: err.message });
    }
});

app.get('/api/tracker-info', async (req, res) => {
    try {
        const tracker = await getTrackerFromGithub();
        res.json(tracker);
    } catch (err) {
        res.status(500).json({ error: err.message });
    }
});

app.get('/api/random-from-folder', async (req, res) => {
    const folder = req.query.folder || '';
    try {
        const files = await getAllCppPaths(folder);
        const tracker = await getTrackerFromGithub();
        const pool = files.filter(f => !tracker.solved.includes(f));

        if (pool.length === 0) return res.json({ error: 'No unsolved questions in this folder!' });

        const randomFile = pool[Math.floor(Math.random() * pool.length)];
        const content = await getFileContent(randomFile);

        // Update tracker in background (on GitHub)
        tracker.manualRequests.push(randomFile);
        await updateTrackerInGithub(tracker);

        res.json({ path: randomFile, name: path.basename(randomFile), content });
    } catch (err) {
        res.status(500).json({ error: err.message });
    }
});

app.get('/api/file-content', async (req, res) => {
    const filePath = req.query.path;
    try {
        const content = await getFileContent(filePath);
        res.json({ path: filePath, name: path.basename(filePath), content });
    } catch (err) {
        res.status(500).json({ error: err.message });
    }
});

app.post('/api/mark-solved', async (req, res) => {
    try {
        const { filePath } = req.body;
        const tracker = await getTrackerFromGithub();
        if (!tracker.solved.includes(filePath)) {
            tracker.solved.push(filePath);
            await updateTrackerInGithub(tracker);
        }
        res.json({ success: true });
    } catch (err) {
        res.status(500).json({ error: err.message });
    }
});

app.post('/api/remove-from-tracker', async (req, res) => {
    const { key, filePath } = req.body;
    try {
        const tracker = await getTrackerFromGithub();
        if (tracker[key]) {
            tracker[key] = tracker[key].filter(f => f !== filePath);
            await updateTrackerInGithub(tracker);
            res.json({ success: true });
        } else {
            res.status(400).json({ error: 'Invalid key' });
        }
    } catch (err) {
        res.status(500).json({ error: err.message });
    }
});

app.post('/api/clear-tracker-key', async (req, res) => {
    const { key } = req.body;
    try {
        const tracker = await getTrackerFromGithub();
        if (tracker[key]) {
            tracker[key] = [];
            await updateTrackerInGithub(tracker);
            res.json({ success: true });
        } else {
            res.status(400).json({ error: 'Invalid key' });
        }
    } catch (err) {
        res.status(500).json({ error: err.message });
    }
});

module.exports.handler = serverless(app);
