const express = require('express');
const os = require('os');

const app = express();
const port = process.env.PORT || 3000;
const group = process.env.GROUP || 'v1';   // 'v1' or 'v2'

// Simulate a small processing delay (50–100 ms)
app.use((req, res, next) => {
    setTimeout(next, Math.floor(Math.random() * 50) + 50);
});

// Route for /api/v1/resource
app.get('/api/v1/resource', (req, res) => {
    res.json({
        server: `${os.hostname()}:${port}`,
        group: 'v1',
        resource: 'data from v1 API',
        timestamp: Date.now()
    });
});

// Route for /api/v2/resource
app.get('/api/v2/resource', (req, res) => {
    res.json({
        server: `${os.hostname()}:${port}`,
        group: 'v2',
        resource: 'data from v2 API',
        timestamp: Date.now()
    });
});

// A simple root endpoint for testing
app.get('/', (req, res) => res.send('OK'));

app.listen(port, () => {
    console.log(`Server ${group} listening on port ${port}`);
});