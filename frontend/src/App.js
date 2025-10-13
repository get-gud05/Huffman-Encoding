import React from "react";
import HuffmanEncoder from "./components/HuffmanEncoder";
import Navbar from "./components/Navbar"
function App() {
  return (
    <div>
      <Navbar />
      <div className="container mt-5">
        <div className="text-center mb-4">
          <h1 className="Headingone">Huffman Encoder</h1>
          <p className="Subheading">
            Enter a string below to encode it using Huffman Encoding
          </p>
        </div>
        <HuffmanEncoder />
      </div>
    </div>
  );
}

export default App;