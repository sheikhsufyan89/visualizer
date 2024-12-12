document.addEventListener("DOMContentLoaded", () => {
  const navValidatedTransactions = document.getElementById(
    "nav-validated-transactions"
  );
  const navSignedTransactions = document.getElementById(
    "nav-signed-transactions"
  );

  const validatedTransactionsSection = document.getElementById(
    "validated-transactions-section"
  );
  const signedTransactionsSection = document.getElementById(
    "signed-transactions-section"
  );

  const navbarLinks = [navValidatedTransactions, navSignedTransactions];
  const sections = [validatedTransactionsSection, signedTransactionsSection];

  function showSection(section, activeNav) {
    sections.forEach((sec) => sec.classList.remove("active"));
    navbarLinks.forEach((link) => link.classList.remove("active"));

    section.classList.add("active");
    activeNav.classList.add("active");
  }

  navValidatedTransactions.addEventListener("click", (e) => {
    e.preventDefault();
    showSection(validatedTransactionsSection, navValidatedTransactions);
  });

  navSignedTransactions.addEventListener("click", (e) => {
    e.preventDefault();
    showSection(signedTransactionsSection, navSignedTransactions);
  });
});

document.addEventListener("DOMContentLoaded", () => {
  const validateButton = document.getElementById("validate");

  validateButton.addEventListener("click", async () => {
    try {
      const response = await fetch("http://localhost:8080/validate", {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
      });

      if (response.ok) {
        const result = await response.json();
        const message = `Success: ${result.result}`;
        showBubbleNotification(message);
      } else {
        const error = await response.json();
        showBubbleNotification(`Error: ${error.message}`, true);
      }
    } catch (error) {
      showBubbleNotification(`An error occurred: ${error.message}`, true);
    }
  });

  function showBubbleNotification(message, isError = false) {
    const bubble = document.createElement("div");
    bubble.className = "bubble-notification";
    bubble.classList.add(isError ? "error" : "success");
    bubble.textContent = message;

    document.body.appendChild(bubble);

    setTimeout(() => {
      bubble.remove();
    }, 3000);
  }
});

document.addEventListener("DOMContentLoaded", async () => {
  const validatedTransactionsList = document.getElementById(
    "validated-transactions-list"
  );

  async function fetchValidatedTransactions() {
    try {
      const response = await fetch(
        "http://localhost:8080/validatedTransactions"
      );
      if (response.ok) {
        const transactions = await response.json();
        validatedTransactionsList.innerHTML = "";
        for (let key in transactions) {
          const transaction = transactions[key];
          const listItem = document.createElement("li");
          listItem.innerHTML = `
            <div class="validatedTransaction">
              <span class="vtx-id">${transaction.id}</span>
              <span class="vtx-sender">Sender: ${transaction.sender}</span>
              <span class="vtx-recipient">Recipient: ${transaction.receiver}</span>
              <span class="vtx-amount"><img src="../assets/solana.png" alt="Solana" class="solana-icon" /> ${transaction.amount}</span>
            </div>
          `;
          // listItem.addEventListener("click", () => {
          //   selectTransaction(transaction, listItem); // If you want to handle transaction selection
          // });
          validatedTransactionsList.appendChild(listItem); // Add to list
        }
      } else {
        alert("Failed to fetch validated transactions.");
      }
    } catch (error) {
      alert("An error occurred while fetching transactions: " + error.message);
    }
  }

  const navValidatedTransactions = document.getElementById(
    "nav-validated-transactions"
  );
  navValidatedTransactions.addEventListener(
    "click",
    fetchValidatedTransactions
  );
  fetchValidatedTransactions();
});

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
          // listItem.classList.add("transaction", "signed");
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

document.addEventListener("DOMContentLoaded", () => {
  const terminal = document.getElementById("terminal");
  const blockButton = document.getElementById("block");

  function showTerminal() {
    terminal.style.display = "block";
    terminal.innerHTML = "";
  }

  function hideTerminal() {
    setTimeout(() => {
      terminal.style.display = "none";
    }, 1);
  }

  function printLine(text, delay = 1) {
    return new Promise((resolve) => {
      let index = 0;
      const interval = setInterval(() => {
        if (index < text.length) {
          terminal.innerHTML += text[index++];
          terminal.scrollTop = terminal.scrollHeight;
        } else {
          clearInterval(interval);
          terminal.innerHTML += "\n";
          resolve();
        }
      }, delay);
    });
  }

  async function fetchAndPrint() {
    try {
      showTerminal();

      const response = await fetch("http://localhost:8080/addBlock", {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
      });

      if (response.ok) {
        const result = await response.json();
        await printLine("API Response Received:");
        await printLine(`Success: ${result.result}`);
      } else {
        const error = await response.json();
        await printLine(`Error: ${error.message}`);
      }
    } catch (error) {
      await printLine(`An error occurred: ${error.message}`);
    } finally {
      hideTerminal();
    }
  }

  blockButton.addEventListener("click", fetchAndPrint);
});
