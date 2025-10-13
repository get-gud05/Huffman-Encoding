const express = require("express");
const bodyParser = require("body-parser");
const cors = require("cors");
const { execFile } = require("child_process");
const path = require("path");

const app = express();
app.use(cors());
app.use(bodyParser.json());

const cExecutable = path.join(__dirname, "../c-code/huffman_encoder");

app.post("/encode", (req, res) => {
  const inputString = req.body.input;

  execFile(cExecutable, [inputString], (error, stdout, stderr) => {
    if (error) {
      console.error("C program error:", error);
      return res.status(500).json({ encoded: "", error: "C program failed" });
    }
    res.json({ encoded: stdout.trim() });
  });
});

const PORT = 5000;
app.listen(PORT, () => console.log(`Server running on port ${PORT}`));
