const express = require('express');
require('dotenv').config();
const cron = require('node-cron');
const fs = require('fs-extra');
const path = require('path');

const { getGithubFolderStructure, getAllCppPaths, getFileContent } = require('./githubService');
const { sendQuestionEmail } = require('./emailService');

const app = express();
const PORT = process.env.PORT || 3000;
const TRACKER_PATH = path.join(__dirname, 'tracker.json');

app.use(express.static('public'));
app.use(express.json());

// Initialize tracker if not exists
if (!fs.existsSync(TRACKER_PATH)) {
    fs.writeJsonSync(TRACKER_PATH, { sentEmails: [], manualRequests: [], solved: [] });
}

async function getTracker() {
    try {
        return await fs.readJson(TRACKER_PATH);
    } catch (err) {
        console.error('Error reading tracker.json, resetting to default:', err.message);
        const defaultValue = { sentEmails: [], manualRequests: [], solved: [] };
        await fs.writeJson(TRACKER_PATH, defaultValue);
        return defaultValue;
    }
}

async function updateTracker(key, value) {
    const tracker = await getTracker();
    if (!tracker[key].includes(value)) {
        tracker[key].push(value);
        await fs.writeJson(TRACKER_PATH, tracker, { spaces: 2 });
    }
}

// Email Cron Job (6AM, 9AM, 12PM, 3PM, 6PM)
cron.schedule('0 6,9,12,15,18 * * *', async () => {
    console.log('Running scheduled question cron job...');
    try {
        const allFiles = await getAllCppPaths();
        const tracker = await getTracker();
        const pool = allFiles.filter(f => !tracker.solved.includes(f) && !tracker.sentEmails.includes(f));
        if (pool.length > 0) {
            const randomFile = pool[Math.floor(Math.random() * pool.length)];
            await sendQuestionEmail(randomFile);
            await updateTracker('sentEmails', randomFile);
        }
    } catch (err) {
        console.error('Cron job error:', err);
    }
});

// Routes
app.get('/', (req, res) => res.sendFile(path.join(__dirname, 'public', 'index.html')));
app.get('/view', (req, res) => res.sendFile(path.join(__dirname, 'public', 'view.html')));

app.get('/api/folder-structure', async (req, res) => {
    try {
        const structure = await getGithubFolderStructure();
        res.json(structure);
    } catch (err) {
        res.status(500).json({ error: err.message });
    }
});

app.get('/random-from-folder', async (req, res) => {
    const folder = req.query.folder || '';
    try {
        const files = await getAllCppPaths(folder);
        const tracker = await getTracker();
        const pool = files.filter(f => !tracker.solved.includes(f));
        if (pool.length === 0) return res.json({ error: 'No unsolved questions in this folder!' });
        const randomFile = pool[Math.floor(Math.random() * pool.length)];
        const content = await getFileContent(randomFile);
        await updateTracker('manualRequests', randomFile);
        res.json({ path: randomFile, name: path.basename(randomFile), content });
    } catch (err) {
        res.status(500).json({ error: err.message });
    }
});

app.get('/file-content', async (req, res) => {
    const filePath = req.query.path;
    try {
        const content = await getFileContent(filePath);
        res.json({ path: filePath, name: path.basename(filePath), content });
    } catch (err) {
        res.status(500).json({ error: err.message });
    }
});

app.post('/mark-solved', async (req, res) => {
    try {
        await updateTracker('solved', req.body.filePath);
        res.json({ success: true });
    } catch (err) {
        res.status(500).json({ error: err.message });
    }
});

app.get('/tracker-info', async (req, res) => {
    try {
        res.json(await getTracker());
    } catch (err) {
        res.status(500).json({ error: err.message });
    }
});

app.post('/remove-from-tracker', async (req, res) => {
    const { key, filePath } = req.body;
    try {
        const tracker = await getTracker();
        if (tracker[key]) {
            tracker[key] = tracker[key].filter(f => f !== filePath);
            await fs.writeJson(TRACKER_PATH, tracker, { spaces: 2 });
            res.json({ success: true });
        } else {
            res.status(400).json({ error: 'Invalid key' });
        }
    } catch (err) {
        res.status(500).json({ error: err.message });
    }
});

app.post('/clear-tracker-key', async (req, res) => {
    const { key } = req.body;
    try {
        const tracker = await getTracker();
        if (tracker[key]) {
            tracker[key] = [];
            await fs.writeJson(TRACKER_PATH, tracker, { spaces: 2 });
            res.json({ success: true });
        } else {
            res.status(400).json({ error: 'Invalid key' });
        }
    } catch (err) {
        res.status(500).json({ error: err.message });
    }
});

// Manual trigger for testing
app.get('/send-test-email', async (req, res) => {
    try {
        const allFiles = await getAllCppPaths();
        if (allFiles.length > 0) {
            const randomFile = allFiles[Math.floor(Math.random() * allFiles.length)];
            await sendQuestionEmail(randomFile);
            res.send(`Test email sent for: ${randomFile}`);
        } else {
            res.send('No files found.');
        }
    } catch (err) {
        res.status(500).send(`Error: ${err.message}`);
    }
});

app.listen(PORT, () => console.log(`Server running at http://localhost:${PORT}`));
