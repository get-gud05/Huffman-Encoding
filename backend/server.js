const express = require("express");
const bodyParser = require("body-parser");
const cors = require("cors");
const { execFile } = require("child_process");
const path = require("path");

const app = express();
app.use(cors());
app.use(bodyParser.json());

const cExecutable = path.join(__dirname, "../c-code/huffman_encoder"); // compiled C program

app.post("/encode", (req, res) => {
  const inputString = req.body.input;

  execFile(cExecutable, [inputString], (error, stdout, stderr) => {
    if (error) {
      console.error("C program error:", error);
      return res.status(500).json({ encoded: "", error: "C program failed" });
    }

    const [encodedPart, statsPart] = stdout.split("__STATS__");
    let originalSize = 0, encodedSize = 0;

    if (statsPart) {
      const origMatch = statsPart.match(/Original:(\d+)/);
      const encMatch = statsPart.match(/Encoded:(\d+)/);
      if (origMatch) originalSize = parseInt(origMatch[1], 10);
      if (encMatch) encodedSize = parseInt(encMatch[1], 10);
    }

    res.json({
      encoded: encodedPart.trim(),
      originalSize,
      encodedSize
    });
  });
});

const PORT = 5000;
app.listen(PORT, () => console.log(`Server running on port ${PORT}`));
