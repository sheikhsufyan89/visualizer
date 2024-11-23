document.addEventListener("DOMContentLoaded", () => {
  const navTransactionForm = document.getElementById("nav-transaction-form");
  const navPendingTransactions = document.getElementById(
    "nav-pending-transactions"
  );
  const navSignedTransactions = document.getElementById(
    "nav-signed-transactions"
  );

  const transactionFormSection = document.getElementById(
    "transaction-form-section"
  );
  const pendingTransactionsSection = document.getElementById(
    "pending-transactions-section"
  );
  const signedTransactionsSection = document.getElementById(
    "signed-transactions-section"
  );

  const navbarLinks = [
    navTransactionForm,
    navPendingTransactions,
    navSignedTransactions,
  ];
  const sections = [
    transactionFormSection,
    pendingTransactionsSection,
    signedTransactionsSection,
  ];

  function showSection(section, activeNav) {
    sections.forEach((sec) => sec.classList.remove("active"));
    navbarLinks.forEach((link) => link.classList.remove("active"));

    section.classList.add("active");
    activeNav.classList.add("active");
  }

  navTransactionForm.addEventListener("click", (e) => {
    e.preventDefault();
    showSection(transactionFormSection, navTransactionForm);
  });

  navPendingTransactions.addEventListener("click", (e) => {
    e.preventDefault();
    showSection(pendingTransactionsSection, navPendingTransactions);
  });

  navSignedTransactions.addEventListener("click", (e) => {
    e.preventDefault();
    showSection(signedTransactionsSection, navSignedTransactions);
  });
});
