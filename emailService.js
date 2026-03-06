const nodemailer = require('nodemailer');
const fs = require('fs-extra');
const path = require('path');
require('dotenv').config();

const transporter = nodemailer.createTransport({
    service: 'gmail',
    auth: {
        user: process.env.GMAIL_USER,
        pass: process.env.GMAIL_PASS
    }
});

const { getFileContent } = require('./githubService');

async function sendQuestionEmail(filePath) {
    const fileName = path.basename(filePath);
    const content = await getFileContent(filePath);

    const mailOptions = {
        from: process.env.GMAIL_USER,
        to: process.env.EMAIL_TO,
        subject: `Daily DSA Challenge: ${fileName}`,
        html: `
            <h2>Time to revise!</h2>
            <p>Today's random question is: <strong>${fileName}</strong></p>
            <p>Path: <code>${filePath}</code></p>
            <hr>
            <pre style="background: #f4f4f4; padding: 10px; border: 1px solid #ddd;"><code>${content}</code></pre>
            <hr>
            <p>Did you solve it? Mark it as solved in the UI to avoid seeing it again.</p>
        `
    };

    return transporter.sendMail(mailOptions);
}

module.exports = {
    sendQuestionEmail
};
