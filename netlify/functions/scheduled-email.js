const {
    getAllCppPaths,
    getTrackerFromGithub,
    updateTrackerInGithub
} = require('../../githubService');
const { sendQuestionEmail } = require('../../emailService');

const handler = async (event, context) => {
    console.log('Running scheduled question job...');
    try {
        const allFiles = await getAllCppPaths();
        const tracker = await getTrackerFromGithub();

        // Filter out solved and already emailed
        const pool = allFiles.filter(f => !tracker.solved.includes(f) && !tracker.sentEmails.includes(f));

        if (pool.length > 0) {
            const randomFile = pool[Math.floor(Math.random() * pool.length)];
            await sendQuestionEmail(randomFile);

            // Persist the sent email to GitHub tracker
            tracker.sentEmails.push(randomFile);
            await updateTrackerInGithub(tracker);

            console.log(`Success: Email sent for ${randomFile}`);
        } else {
            console.log('No new questions available.');
        }
    } catch (err) {
        console.error('Job error:', err.message);
    }
};

// Netlify Scheduled Functions export
module.exports.handler = handler;
