// server.js
const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');
const fs = require('fs');
const path = require('path');

const app = express();
const PORT = 3000;

// Middleware
app.use(cors());
app.use(bodyParser.json());

// Path to tasks.json
const tasksFilePath = path.join(__dirname, 'tasks.json');

// Load tasks from tasks.json
app.get('/api/tasks', (req, res) => {
    fs.readFile(tasksFilePath, 'utf8', (err, data) => {
        if (err) {
            return res.status(500).send('Error reading tasks file');
        }
        res.json(JSON.parse(data));
    });
});

// Save tasks to tasks.json
app.post('/api/tasks', (req, res) => {
    const tasksData = JSON.stringify(req.body, null, 2);
    fs.writeFile(tasksFilePath, tasksData, 'utf8', (err) => {
        if (err) {
            return res.status(500).send('Error saving tasks file');
        }
        res.send('Tasks saved successfully');
    });
});

// Start the server
app.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});
