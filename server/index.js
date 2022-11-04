const express = require('express')
const app = express()
const port = 3000

app.get('/', (req, res) => {
  res.send('Hello World!')
})

app.get('/download', function(req, res){
  const file = `${__dirname}/macaoufo.zip`;
  res.download(file); // Set disposition and send it.
});

// app.get('/test', function (req, res) {
  // require('child_process').exec('start "" "E:\\codeTest\\expressjs\\cacao"');
// });

app.use('/cacao', express.static('./Do99'))

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
})