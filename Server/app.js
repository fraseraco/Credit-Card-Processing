// express setup
import express from 'express';
const app = express();
const port = 3000;

// sqlite setup
import sqlite3 from "sqlite3";
const dbFilename = "./db/creditCardAccount.db";
const db = new sqlite3.Database(dbFilename, sqlite3.OPEN_READWRITE);

// Middleware to parse JSON request body
app.use(express.json());



app.post('/', (req, res) => {
    console.log(req.body);
    const { creditCardNumber, pin, transactionAmount, expirationMonth, expirationYear } = req.body;

    if (!creditCardNumber || !pin || !transactionAmount || !expirationMonth || !expirationYear) {
        return res.status(400).json({ status: "Declined", error: 'Missing required fields' });
    }

    // Query the database
    const query = `
        SELECT * FROM CARDS where Card_num = '${creditCardNumber}';
    `;
    console.log(query);
    db.all(query, (err, rows) => {

        if (err || rows.length > 1) {
            console.error('Database error:', err.message);
            return res.status(500).json({ error: 'Internal server error' });
        }




        if (rows.length === 0) {
            return res.status(406).json({status: "Declined", reason: "Card not found"})
        }

        // verify expiration date
        const row = rows[0];

        console.log(row);

        const reqBodyDate = new Date(expirationYear, expirationMonth);
        const sqlResDate = new Date(Number(row.Exp_year), Number(row.Exp_month));

        if (reqBodyDate.toDateString() !== sqlResDate.toDateString() || reqBodyDate < Date.now()) {
            return res.status(406).json({status: "Declined", reason: "Expired"})
        }

        // verify pin
        if (Number(pin) !== Number(row.Pin)) {
            return res.status(406).json({status: "Declined", reason: "Invalid PIN"})
        }

        // verify balance
        if (transactionAmount > row.Balance) {
            return res.status(406).json({status: "Declined", reason: "Insufficient balance"})
        }

        // update balance
        const updatedBalance = row.Balance - transactionAmount;
        const balanceUpdateQuery = `
            UPDATE CARDS SET Balance = ${updatedBalance} WHERE Card_num = '${creditCardNumber}'
        `
        db.all(balanceUpdateQuery, (err, rows) => {
            if (err) console.log(err);
        });

        // send accepted response to user
        return res.status(200).json({status: "Approved"})
    });

});


app.get('/', (req, res) => {
  res.send('Hello World!')
})

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
})