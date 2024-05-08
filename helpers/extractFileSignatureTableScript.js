
const table = document.getElementById('myTable');

let data = [];

for (let row of table.tBodies[0].rows) {
    // Extract hex signature from the first cell
    try {
      var hexSignature = row.cells[0].textContent.trim();
    } catch (e) {
      var hexSignature = none;
    }
    // Extract extensions from the fourth cell
    try {
      // handles instances of multiple extensions
      var extensions = row.cells[3].textContent.trim().split(/\s+/).join(',');
    } catch (e) {
      var extensions = null;
    }

    if (!hexSignature || !extensions) continue;

    data.push(`"${hexSignature}","${extensions}"`);
}

const csvContent = "Hex Signature,Extension\n" + data.join('\n');

const blob = new Blob([csvContent], { type: 'text/csv;charset=utf-8;' });

const link = document.createElement('a');
link.href = URL.createObjectURL(blob);
link.download = 'hex-signatures.csv';

document.body.appendChild(link);
link.click();
document.body.removeChild(link);