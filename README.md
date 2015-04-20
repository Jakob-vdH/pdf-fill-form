<img src="http://res.cloudinary.com/tpisto/image/upload/v1428317033/pdf-fill-form-logo_rlfj7o.png" width="400"><br/>
PDF Fill Form (**pdf-fill-form**) is Node.js native C++ library for filling PDF forms. Created PDF file is returned back as Node.js Buffer object for further processing or saving - *whole process is done in memory*. Library offers methods to return filled PDF also as PDF file where pages are converted to images.

Libary uses internally Poppler QT4 for PDF form reading and filling. Cairo is used for PDF creation from page images (when parameter { "save": "imgpdf" } is used). 
##Features
* Supports reading and writing the following PDF form field types: TextField and Checkbox 
* You can write following files:
	* PDF
	* PDF where pages are converted to images
* All the work is done in memory - no temporary files created
* Results are returned in Node.js Buffer -object
* Not using the PDFtk -executable - instead we use the Poppler library

##Examples
###Using promises
```javascript
var pdfFillForm = require('pdf-fill-form');

pdfFillForm.read('test.pdf')
.then(function(result) {
    console.log(result);
}, function(err) {
	console.log(err);
});
```
```javascript
var pdfFillForm = require('pdf-fill-form');
var fs = require('fs');

pdfFillForm.write('test.pdf', { "myField": "myField fill value" }, { "save": "pdf" } )
.then(function(result) {
	fs.writeFile("test123.pdf", result, function(err) {
		if(err) {
	   		return console.log(err);
	   	}
	   	console.log("The file was saved!");
	}); 
}, function(err) {
  	console.log(err);
});

```
###Using callbacks
To **read** all form fields:  

```javascript
var pdfFillForm = require('pdf-fill-form');

var pdfFields = pdfFillForm.readSync('test.pdf');
console.log(pdfFields);
```
To **write** form fields (synchronous) to PDF:

```javascript
var pdfFillForm = require('pdf-fill-form');
var fs = require('fs');

// Use here the field names you got from read
var pdf = pdfFillForm.writeSync('test.pdf', 
	{ "myField": "myField fill value" }, { "save": "pdf" } );
fs.writeFileSync('filled_test.pdf', pdf);
```
To **write** form fields (aynchronous) to PDF:

```javascript
var pdfFillForm = require('pdf-fill-form');
var fs = require('fs');

// Use here the field names you got from read
pdfFillForm.writeAsync('test.pdf', 
	{ "myField": "myField fill value" }, { "save": "pdf" }, 
	function(err, pdf) {
		fs.writeFile("filled_test.pdf", pdf, function(err){});
	}
);
```
To **write** form fields to PDF where pages are converted to images:  

Use parameter { "save": "imgpdf" }

##Installation

###OS X
Preferable method to install library dependencies is via [Homebrew](http://brew.sh/)

```
$ brew install cairo poppler
```
After dependencies are successfully installed, you can install the library:

```
$ npm install pdf-fill-form
```  
> Homebrew users who get error regarding xcb-shm  
> The fix is to add this to your bash profile / environment: export PKG_CONFIG_PATH=/opt/X11/lib/pkgconfig

###Linux - Ubuntu (trusty)
```
$ sudo apt-get install libpoppler-qt4-dev libcairo2-dev
$ npm install pdf-fill-form
```
###Linux - Debian (wheezy)
We need newer Poppler library than the current in Wheezy distribution: 

```
$ sudo add-apt-repository "deb http://http.debian.net/debian wheezy-backports main"     
$ sudo apt-get update
```
Then install packages

```
$ sudo apt-get install libcairo2-dev
$ sudo apt-get -t wheezy-backports install libpoppler-qt4-dev 
$ npm install pdf-fill-form
```
##Todo
* Tests
* Refactoring
* Support for other form field types than CheckBox and TextField

##Authors
- [Tommi Pisto](https://github.com/tpisto)

## License
MIT  

NOTE ABOUT LIBRARY DEPENDENCIES!   
*Poppler has* ***GPL*** *license.* Cairo has LGPL.