import React from "react";
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faMinimize } from '@fortawesome/free-solid-svg-icons';
import '../App.css';
function Navbar() {
  return (
    <nav className="navbar ">
      <div className="container d-flex justify-content-center">
        <a className="navbar-brand" href="#">
          <FontAwesomeIcon icon={faMinimize} className="brandicon me-2" />
          <span className="brandname">BitCruncher</span>
        </a>
      </div>
    </nav>
  );
}

export default Navbar;
