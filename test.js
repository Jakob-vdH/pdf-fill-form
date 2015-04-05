var a = require('lib/piston-poppler.js');
var fs = require('fs');

console.log(a.readFields('ilmo.pdf'));

var myPdf = a.writeFields('ilmo.pdf', { "Sivun1Tekstit.5.0": "Test Oy", "Sivun2bTekstit.0.25": "jeps", "b": "c" }, { "save": "imgpdf" });
fs.writeFile("test123.pdf", myPdf, function(err) {
  if(err) {
      return console.log(err);
  }
  console.log("The file was saved!");
}); 
