const express = require('express');
const app = express();
const port = 3000;

// Middleware to parse JSON request body
app.use(express.json());


app.post('/', (req, res) => {
    console.log(req.body);
    const { creditCardNumber, pin, transactionAmount, expirationDate } = req.body;

    if (!creditCardNumber || !pin || !transactionAmount || !expirationDate) {
        return res.status(400).json({ status: "Declined", error: 'Missing required fields' });
    }

    // Query the database


    const transaction = {status: "Approved"}; // fake
    return res.json(transaction);
});


app.get('/', (req, res) => {
  res.send('Hello World!')
})

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
})