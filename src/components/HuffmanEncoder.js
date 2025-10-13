import React, { useState } from "react";
import '../App.css';

function HuffmanEncoder() {
  const [input, setInput] = useState("");
  const [encoded, setEncoded] = useState("");

  const handleEncode = async () => {
    setEncoded("Encoded output will appear here (once backend is connected)");
  };

  return (
    <div className="d-flex flex-column align-items-center">
      <textarea
        className="form-control mb-3"
        placeholder="Enter text to encode..."
        rows={5}
        value={input}
        onChange={(e) => setInput(e.target.value)}
      />
      <button className="encbtn btn mb-3" onClick={handleEncode}>
        Encode
      </button>

      {encoded && (
        <div className="card w-100">
          <div className="card-body">
            <h5 className="card-title">Encoded String:</h5>
            <p className="card-text">{encoded}</p>
          </div>
        </div>
      )}
    </div>
  );
}

export default HuffmanEncoder;