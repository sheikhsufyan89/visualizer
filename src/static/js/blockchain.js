// const container = document.getElementById("blockchain-container");

// const blocks = Array.from({ length: 30 }, (_, i) => ({
//   blockNumber: i + 1,
//   hash: `hash${i + 1}`,
//   previousHash: i === 0 ? "000000" : `hash${i}`,
// }));

// function renderBlockchain(blocks) {
//   let currentRow = null;
//   blocks.forEach((block, index) => {
//     if (index % 5 === 0) {
//       currentRow = document.createElement("div");
//       currentRow.classList.add("row");
//       if (Math.floor(index / 5) % 2 !== 0) {
//         currentRow.classList.add("reverse");
//       }
//       container.appendChild(currentRow);
//     }
//     const blockElement = document.createElement("div");
//     blockElement.classList.add("block");
//     blockElement.innerHTML = `
//       <h3>Block ${block.blockNumber}</h3>
//       <p>Hash: ${block.hash}</p>
//       <p>Previous: ${block.previousHash}</p>
//     `;
//     currentRow.appendChild(blockElement);

//     if ((index + 1) % 5 !== 0 && index !== blocks.length - 1) {
//       const arrowElement = document.createElement("div");
//       arrowElement.classList.add("arrow");
//       arrowElement.textContent = "⟶";
//       currentRow.appendChild(arrowElement);
//     }
//   });
// }

// renderBlockchain(blocks);

const container = document.getElementById("blockchain-container");

async function fetchBlockchain() {
  try {
    const response = await fetch("http://localhost:8080/blockchain");
    if (!response.ok) {
      throw new Error("Failed to fetch blockchain data");
    }
    const blockchainData = await response.json();

    const blocks = Object.values(blockchainData).map((block) => ({
      blockNumber: block.index,
      hash: block.hash,
      previousHash: block.previousHash,
    }));

    renderBlockchain(blocks);
  } catch (error) {
    console.error("Error fetching blockchain data:", error);
  }
}

function renderBlockchain(blocks) {
  let currentRow = null;
  container.innerHTML = "";
  blocks.forEach((block, index) => {
    if (index % 5 === 0) {
      currentRow = document.createElement("div");
      currentRow.classList.add("row");
      if (Math.floor(index / 5) % 2 !== 0) {
        currentRow.classList.add("reverse");
      }
      container.appendChild(currentRow);
    }
    const blockElement = document.createElement("div");
    blockElement.classList.add("block");
    blockElement.innerHTML = `
      <h3>Block ${block.blockNumber}</h3>
      <p>Hash: ${block.hash}</p>
      <p>Previous: ${block.previousHash}</p>
    `;
    currentRow.appendChild(blockElement);

    if ((index + 1) % 5 !== 0 && index !== blocks.length - 1) {
      const arrowElement = document.createElement("div");
      arrowElement.classList.add("arrow");
      arrowElement.textContent = "⟶";
      currentRow.appendChild(arrowElement);
    }
  });
}

fetchBlockchain();
