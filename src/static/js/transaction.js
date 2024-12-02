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
          // listItem.classList.add("transaction", "pending");
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

const hashButton = document.getElementById("hash-button");
let selectedTransaction = null;
function selectTransaction(transaction, listItem) {
  const previousSelected = document.querySelector(".selected");
  if (previousSelected) previousSelected.classList.remove("selected");
  listItem.classList.add("selected");
  selectedTransaction = transaction;
  hashButton.disabled = false;
}

let customHashFunction = "";

function getCustomHashFunction() {
  const textEditor = document.getElementById("text-editor");
  return textEditor ? textEditor.innerText.trim() : "";
}

let textEditor = document.getElementById("text-editor");
let closeButton = document.getElementById("close-button");

hashButton.addEventListener("click", () => {
  if (selectedTransaction) {
    if (currentUser.role === "custom") {
      textEditor.style.display = "block";
      closeButton.classList.add("show");
      closeButton.addEventListener(
        "click",
        async () => {
          textEditor.style.display = "none";
          closeButton.classList.remove("show");
          customHashFunction = getCustomHashFunction();
          alert("Dispatching with custom hash function: " + customHashFunction);
          await sendHashRequest(customHashFunction);
        },
        { once: true }
      );
    } else {
      const standardHashFunction = "";
      alert("You are a standard user. Dispatching with default hash function.");
      sendHashRequest(standardHashFunction);
    }
  } else {
    alert("No transaction selected.");
  }
});

async function sendHashRequest(hashfunction) {
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
        hashfunction: hashfunction,
      }),
    });

    if (response.ok) {
      const result = await response.json();
      alert("Transaction hashed successfully! Hash: " + result.hash);
    } else {
      const error = await response.json();
      alert("HashFunction incorrect.");
    }
  } catch (error) {
    alert("HashFunction incorrect.");
  }
}

document.addEventListener("DOMContentLoaded", async () => {
  const signedTransactionsList = document.getElementById(
    "signed-transactions-list"
  );

  async function fetchSignedTransactions() {
    try {
      const response = await fetch("http://localhost:8080/signedTransactions");
      if (response.ok) {
        const transactions = await response.json();
        signedTransactionsList.innerHTML = "";
        for (let key in transactions) {
          const transaction = transactions[key];
          const listItem = document.createElement("li");
          listItem.innerHTML = `
        <div class="transaction-card">
  <span class="transaction-id"><strong>ID:</strong> ${transaction.id}</span>
  <span class="transaction-sender"><strong>Sender:</strong> ${
    transaction.sender
  }</span>
  <span class="transaction-recipient"><strong>Recipient:</strong> ${
    transaction.receiver
  }</span>
  <span class="transaction-amount">
    <strong>Amount:</strong>
 <img src="../assets/solana.png" alt="Solana" class="solana-icon" />
    ${transaction.amount}
  </span>
  <span class="transaction-signed-by"><strong>Signed by:</strong> ${
    transaction.signed_by
  }</span>
  <span class="transaction-hash"><strong>Hash:</strong> ${
    transaction.hash
  }</span>
  <span class="transaction-time"><strong>Time:</strong> ${new Date(
    transaction.time * 1000
  ).toLocaleString()}</span>
</div>

        `;
          listItem.addEventListener("click", () => {
            selectTransaction(transaction, listItem);
          });
          signedTransactionsList.appendChild(listItem);
        }
      } else {
        alert("Failed to fetch signed transactions.");
      }
    } catch (error) {
      alert(
        "An error occurred while fetching signed transactions: " + error.message
      );
    }
  }
  const navSignedTransactions = document.getElementById(
    "nav-signed-transactions"
  );
  navSignedTransactions.addEventListener("click", fetchSignedTransactions);
  fetchSignedTransactions();
});
