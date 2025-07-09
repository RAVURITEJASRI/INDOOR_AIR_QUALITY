function doGet(e) {
  const ss = SpreadsheetApp.openById("1d0whfaDoS81ynVFjGDJOTLI5O2oERMhsGUioc8uQlNU");
  const sheet = ss.getSheetByName("Sheet1");

  const user = e.parameter.user;
  const pass = e.parameter.pass;

  // Only get required columns for faster performance
  const users = sheet.getRange(2, 1, sheet.getLastRow() - 1, 2).getValues(); // col A & B from row 2

  for (let i = 0; i < users.length; i++) {
    if (users[i][0] === user && users[i][1] === pass) {
      return ContentService.createTextOutput("success");
    }
  }
  return ContentService.createTextOutput("fail");
}

function doPost(e) {
  const ss = SpreadsheetApp.openById("1d0whfaDoS81ynVFjGDJOTLI5O2oERMhsGUioc8uQlNU");
  const sheet = ss.getSheetByName("Sheet1");
  const user = e.parameter.user;
  const pass = e.parameter.pass;

  // Directly add row (fastest method)
  sheet.appendRow([user, pass]);

  return ContentService.createTextOutput("created");
}
