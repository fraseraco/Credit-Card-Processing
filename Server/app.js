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
    console.log("Beginning card processing")
    const { creditCardNumber, pin, transactionAmount, expirationMonth, expirationYear } = req.body;

    if (!creditCardNumber || !pin || !transactionAmount || !expirationMonth || !expirationYear) {
        return res.status(400).json({ status: "Declined", error: 'Missing required fields' });
    }

    // Query the database
    const query = `
        SELECT * FROM CARDS where Card_num = '${creditCardNumber}';
    `;
    console.log("Querying database...")
    db.all(query, (err, rows) => {

        if (err || rows.length > 1) {
            console.error('Database error:', err.message);
            return res.status(500).json({ error: 'Internal server error' });
        }

        console.log("Verifying card exists...")
        if (rows.length === 0) {
            return res.status(406).json({status: "Declined", reason: "Card not found"})
        }
        console.log("Card found")
        // verify expiration date
        console.log("Verifying expiration date...")
        const row = rows[0];

        const reqBodyDate = new Date(expirationYear, expirationMonth);
        const sqlResDate = new Date(Number(row.Exp_year), Number(row.Exp_month));

        if (reqBodyDate.toDateString() !== sqlResDate.toDateString() || reqBodyDate < Date.now()) {
            console.log("Expiration date failed verification")
            return res.status(406).json({status: "Declined", reason: "Expired"})
        }
        console.log("Expiration date verified")

        // verify pin
        console.log("Verifying pin...")
        if (Number(pin) !== Number(row.Pin)) {
            console.log("Pin failed verification")
            return res.status(406).json({status: "Declined", reason: "Invalid PIN"})
        }
        console.log("Pin verified")

        // verify balance
        console.log("Verifying balance...")
        if (transactionAmount > row.Balance) {
            console.log("Balance failed verification")
            return res.status(406).json({status: "Declined", reason: "Insufficient balance"})
        }
        console.log("Balance verified")

        // update balance
        console.log("Updating balance...")
        const updatedBalance = row.Balance - transactionAmount;
        const balanceUpdateQuery = `
            UPDATE CARDS SET Balance = ${updatedBalance} WHERE Card_num = '${creditCardNumber}'
        `
        db.all(balanceUpdateQuery, (err, rows) => {
            console.log("Unable to update balance")
            if (err) console.log("Error: " + err);
        });
        console.log("Balance updated")
        console.log("Transaction approved")
        console.log("Sending data back to CC terminal")

        // send accepted response to user
        return res.status(200).json({status: "Approved"})
    });

});

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
})