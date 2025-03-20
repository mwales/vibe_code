const canvas = document.getElementById('tetris');
const ctx = canvas.getContext('2d');

// Grid dimensions
const ROWS = 20;
const COLS = 10;
const BLOCK_SIZE = 30;

// Define vibed-out 5 block shapes
const BLOCKS = [
  // T-shape
  [
    [[1, 1, 1, 0], [0, 1, 0, 0], [0, 0, 1, 0]], // Rotation 0
    [[0, 0, 1, 0], [1, 1, 1, 0], [0, 0, 0, 0]], // Rotation 1
    [[0, 0, 1, 0], [0, 1, 1, 1], [0, 0, 0, 0]], // Rotation 2
    [[0, 1, 0, 0], [1, 1, 1, 0], [0, 0, 0, 0]], // Rotation 3
  ],
  // L-shape
  [
    [[1, 1, 1, 1], [1, 0, 0, 0]], // Rotation 0
    [[1, 1, 1, 0], [0, 0, 1, 1]], // Rotation 1
    [[0, 1, 1, 1], [0, 0, 0, 1]], // Rotation 2
    [[1, 0, 0, 0], [1, 1, 1, 0]], // Rotation 3
  ],
  // Zigzag shape (S-ish)
  [
    [[1, 1, 0, 0], [0, 1, 1, 1]], // Rotation 0
    [[0, 1, 1, 1], [1, 1, 0, 0]], // Rotation 1
    [[1, 1, 0, 0], [0, 1, 1, 1]], // Rotation 2
    [[0, 1, 1, 1], [1, 1, 0, 0]], // Rotation 3
  ],
  // Upside-down L-shape
  [
    [[0, 1, 1, 0], [1, 1, 1, 0]], // Rotation 0
    [[1, 1, 0, 0], [0, 1, 1, 1]], // Rotation 1
    [[0, 1, 1, 0], [1, 1, 1, 0]], // Rotation 2
    [[1, 1, 0, 0], [0, 1, 1, 1]], // Rotation 3
  ],
  // T-Block Combo
  [
    [[1, 0, 0, 1], [1, 1, 1, 0]], // Rotation 0
    [[1, 1, 0, 0], [0, 1, 1, 1]], // Rotation 1
    [[1, 0, 0, 1], [1, 1, 1, 0]], // Rotation 2
    [[1, 1, 0, 0], [0, 1, 1, 1]], // Rotation 3
  ],
];

// Game state
let currentBlock;
let currentX = 4;
let currentY = 0;
let currentRotation = 0; // Track the current rotation of the block
let grid = Array.from({ length: ROWS }, () => Array(COLS).fill(0));
let score = 0;
let level = 1; // Add the level for difficulty

// Function to draw the background grid
function drawBackgroundGrid() {
  ctx.strokeStyle = 'lightgray';
  ctx.lineWidth = 0.5;

  for (let row = 0; row < ROWS; row++) {
    for (let col = 0; col < COLS; col++) {
      ctx.strokeRect(col * BLOCK_SIZE, row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
    }
  }
}

// Function to draw the game grid and the current block
function drawGrid() {
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  drawBackgroundGrid();

  // Draw current block with color change effect
  const blockShape = currentBlock[currentRotation];
  for (let row = 0; row < blockShape.length; row++) {
    for (let col = 0; col < blockShape[row].length; col++) {
      if (blockShape[row][col] === 1) {
        // Vibrant color effect for block
        ctx.fillStyle = `hsl(${Math.random() * 360}, 100%, 50%)`;
        ctx.fillRect((currentX + col) * BLOCK_SIZE, (currentY + row) * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
      }
    }
  }

  // Draw the landed blocks
  for (let row = 0; row < ROWS; row++) {
    for (let col = 0; col < COLS; col++) {
      if (grid[row][col] === 1) {
        ctx.fillStyle = 'green'; // Color for the landed block
        ctx.fillRect(col * BLOCK_SIZE, row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
      }
    }
  }

  // Update score and level
  document.getElementById('score').textContent = `Score: ${score} | Level: ${level}`;
}

// Function to generate a new block
function generateBlock() {
  const randomIndex = Math.floor(Math.random() * BLOCKS.length);
  currentBlock = BLOCKS[randomIndex];
  currentRotation = 0; // Reset rotation when generating a new block
  currentX = 4;
  currentY = 0;
}

// Function to move the block down
function moveDown() {
  currentY++;
  if (isCollision()) {
    currentY--;
    placeBlock();
    clearRows();
    generateBlock();
    increaseLevel(); // Increase level after each block placement
  }
  drawGrid();
}

// Function to check if the current block collides
function isCollision() {
  const blockShape = currentBlock[currentRotation];
  for (let row = 0; row < blockShape.length; row++) {
    for (let col = 0; col < blockShape[row].length; col++) {
      if (blockShape[row][col] === 1) {
        if (currentY + row >= ROWS || currentX + col < 0 || currentX + col >= COLS || grid[currentY + row][currentX + col] !== 0) {
          return true;
        }
      }
    }
  }
  return false;
}

// Function to place the block on the grid
function placeBlock() {
  const blockShape = currentBlock[currentRotation];
  for (let row = 0; row < blockShape.length; row++) {
    for (let col = 0; col < blockShape[row].length; col++) {
      if (blockShape[row][col] === 1) {
        grid[currentY + row][currentX + col] = 1;
      }
    }
  }
}

// Function to clear full rows
function clearRows() {
  for (let row = ROWS - 1; row >= 0; row--) {
    if (grid[row].every(cell => cell === 1)) {
      grid.splice(row, 1);
      grid.unshift(Array(COLS).fill(0));
      score += 10;
    }
  }
}

// Function to increase the level based on score
function increaseLevel() {
  if (score >= level * 100) {
    level++;
    clearInterval(gameInterval);
    gameInterval = setInterval(moveDown, 500 - (level * 50)); // Speed up the game as level increases
  }
}

// Function to handle Up and Down arrow crazy actions
document.addEventListener('keydown', (e) => {
  if (e.key === 'ArrowLeft') {
    currentX--;
    if (isCollision()) currentX++;
  } else if (e.key === 'ArrowRight') {
    currentX++;
    if (isCollision()) currentX--;
  } else if (e.key === 'ArrowDown') {
    // Down arrow does wild transformations: squish or split
    squishBlock();
  } else if (e.key === 'ArrowUp') {
    // Up arrow does crazy rotations and flips
    performShenanigans();
  }
  drawGrid();
});

// Perform some crazy block shenanigans
function performShenanigans() {
  const randomAction = Math.floor(Math.random() * 3); // Limit random actions to rotation, flip, and stretch
  
  if (randomAction === 0) {
    // Rotate like usual
    currentRotation = (currentRotation + 1) % currentBlock.length;
  } else if (randomAction === 1) {
    // Flip upside down
    flipBlock();
  } else if (randomAction === 2) {
    // Stretch block to crazy size
    stretchBlock();
  }
}

// Flip the block upside down
function flipBlock() {
  currentBlock[currentRotation] = currentBlock[currentRotation].reverse().map(row => row.reverse());
}

// Stretch the block to make it look wacky
function stretchBlock() {
  currentBlock[currentRotation] = currentBlock[currentRotation].map(row => row.concat(row)); // Stretch horizontally
}

// Squish the block
function squishBlock() {
  currentBlock[currentRotation] = currentBlock[currentRotation].map(row => row.slice(0, Math.floor(row.length / 2))); // Squish horizontally
}

// Start the game
let gameInterval;
function startGame() {
  generateBlock();
  gameInterval = setInterval(moveDown, 500); // Move the block down every 500ms
}

startGame();

