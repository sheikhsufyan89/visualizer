let currentUser = null;

document.addEventListener("DOMContentLoaded", async () => {
  try {
    const response = await fetch("http://localhost:8080/currentUser");
    if (response.status === 200) {
      const result = await response.json();
      document.getElementById("username-display").textContent = result.username;
      currentUser = result;
    } else {
      alert("User is not logged in.");
    }
  } catch (error) {
    alert("An error occurred: " + error.message);
  }
});
