const http = require('http');
require('dotenv');
const port = process.env.PORT || 3001;

const {Hello, Pangkat, Prime} = require('./build/Release/addon');
// `Hello` function returns a string, so we have to console.log it!
// console.log(Hello());
// console.log(Pangkat(5));
const server = http.createServer((req, res) => {
    let hello = Hello();
    let pangkat = Pangkat(100000);
    let primeMsg = Prime(100000);
    res.writeHead(200, {
        'Content-Type':'application/json'
    });
    let message = JSON.stringify({
        msg : hello,
        prime : primeMsg,
        pangkat : pangkat
    });
    res.write(message)
    res.end();
});

server.listen(port, () => {
    console.log("Server listen in port %d", port);
});

// note that the compiled addon is placed under following path


