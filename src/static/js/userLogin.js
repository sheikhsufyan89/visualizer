// Handle the form submission
document
  .getElementById("loginForm")
  .addEventListener("submit", function (event) {
    event.preventDefault();

    // Get input values
    const username = document.getElementById("username").value;
    const password = document.getElementById("password").value;
    const userType = document.getElementById("userType").value;

    if (
      username === "test" &&
      password === "password123" &&
      userType === "standard"
    ) {
      window.location.href = "standard_dashboard.html";
    } else if (
      username === "customuser" &&
      password === "custompass" &&
      userType === "custom"
    ) {
      window.location.href = "custom_dashboard.html";
    } else {
      document.getElementById("errorMessage").style.display = "block";
    }
  });
