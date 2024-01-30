const { log } = require('console');
const net = require('net');
const readline = require('readline');

const client = new net.Socket();

// Read commands from the command line
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

// Connect to the server
client.connect(9999, '127.0.0.1', () => {
  console.log('Connected to server');

  // Start reading commands
  rl.question('Enter a command (type "exit" to disconnect): ', (command) => {
    if (command.toLowerCase() === 'exit') {
      // If the user types "exit," close the connection and exit the program
      client.end();
      rl.close();
    } else {
      // Otherwise, send the command to the server
      client.write(command);
    }
  });
});

// Listen for data from the server
client.on('data', (data) => {
  const receivedString = data.toString();
  // Convert the string to an array (assuming the server sends a newline-separated list)
  const stringArray = receivedString.replaceAll("\uFFFD", "\n").replaceAll("\x12", "\n").split('\n');

  if (stringArray.length > 0) {
    stringArray.forEach((str) => {
      console.log(`${str}`);
    });
  } else {
    console.log('Received response from server:', receivedString);
  }

  // Prompt the user for the next command
  rl.question('Enter a command (type "exit" to disconnect): ', (command) => {
    if (command.toLowerCase() === 'exit') {
      // If the user types "exit," close the connection and exit the program
      client.end();
      rl.close();
    } else {
      // Otherwise, send the command to the server
      client.write(command);
    }
  });
});

// Listen for the connection close event
client.on('close', () => {
  console.log('Connection closed');
});
