document.addEventListener("DOMContentLoaded", async () => {
  const transactionForm = document.getElementById("transaction-form");

  transactionForm.addEventListener("submit", async (event) => {
    event.preventDefault();

    const data = {
      sender: currentUser.username,
      recipient: event.target.recipient.value,
      amount: parseFloat(event.target.amount.value),
    };

    try {
      const response = await fetch("http://localhost:8080/addTransaction", {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify(data),
      });

      if (response.ok) {
        const result = await response.json();
        alert(
          "Transaction added successfully! Transaction ID: " +
            result.transactionId
        );
      } else {
        const error = await response.json();
        alert("Error: " + error.message);
      }
    } catch (error) {
      alert("An error occurred: " + error.message);
    }
  });
});

const hashButton = document.getElementById("hash-button");
let selectedTransaction = null;
function selectTransaction(transaction, listItem) {
  const previousSelected = document.querySelector(".selected");
  if (previousSelected) previousSelected.classList.remove("selected");
  listItem.classList.add("selected");
  selectedTransaction = transaction;
  hashButton.disabled = false;
}

hashButton.addEventListener("click", async () => {
  if (selectedTransaction) {
    try {
      const response = await fetch("http://localhost:8080/hash", {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },

        body: JSON.stringify({
          transactionId: selectedTransaction.id,
          sender: selectedTransaction.sender,
          receiver: selectedTransaction.receiver,
          amount: parseFloat(selectedTransaction.amount),
          signed_by: currentUser.username,
        }),
      });
      if (response.ok) {
        const result = await response.json();
        alert(
          "Transaction hashed successfully! Transaction ID: " + timestampString
        );
      } else {
        const error = await response.json();
        alert("Error: " + error.message);
      }
    } catch (error) {
      alert("An error occurred: " + error.message);
    }
  } else {
    alert("No transaction selected.");
  }
});

document.addEventListener("DOMContentLoaded", async () => {
  const pendingTransactionsList = document.getElementById(
    "pending-transactions-list"
  );

  async function fetchPendingTransactions() {
    try {
      const response = await fetch("http://localhost:8080/pendingTransactions");
      if (response.ok) {
        const transactions = await response.json();
        pendingTransactionsList.innerHTML = "";
        for (let key in transactions) {
          const transaction = transactions[key];
          const listItem = document.createElement("li");
          listItem.classList.add("transaction-item");
          listItem.innerHTML = `
          <div class="transaction">
            <span class="tx-id">${transaction.id}</span>
            <span class="tx-sender">Sender: ${transaction.sender}</span>
            <span class="tx-recipient">Recipient: ${transaction.receiver}</span>
            <span class="tx-amount"><img src="../assets/solana.png" alt="Solana" class="solana-icon" /> ${transaction.amount}</span>
          </div>
        `;
          listItem.addEventListener("click", () => {
            selectTransaction(transaction, listItem);
          });
          pendingTransactionsList.appendChild(listItem);
        }
      } else {
        alert("Failed to fetch pending transactions.");
      }
    } catch (error) {
      alert("An error occurred while fetching transactions: " + error.message);
    }
  }
  const navPendingTransactions = document.getElementById(
    "nav-pending-transactions"
  );
  navPendingTransactions.addEventListener("click", fetchPendingTransactions);
  fetchPendingTransactions();
});
