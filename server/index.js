const express = require('express')
const app = express()
const port = 7879


app.all("*", (req, res, next) => {
  console.log('log =====================> ', req._parsedUrl); // do anything you want here
  next();
});

app.get('/', (req, res) => {
  res.send('hello')
})

app.get('/download', function(req, res){
  const file = `${__dirname}/macaoufo.zip`;
  res.download(file); // Set disposition and send it.
});

app.get('/remote-assets/version.manifest', function(req, res){
  const file = `${__dirname}/version.manifest`;
  res.download(file); // Set disposition and send it.
});

app.get('/remote-assets/project.manifest', function(req, res){
  // const file = `${__dirname}/project.manifest`;
  const file = `${__dirname}/800f94fd-7424-4202-9629-d3ca77f3b72d.manifest`;
  res.download(file); // Set disposition and send it.
});

app.get('/version.manifest', function(req, res){
  const file = `${__dirname}/version.manifest`;
  res.download(file); // Set disposition and send it.
});

app.get('/project.manifest', function(req, res){
  const file = `${__dirname}/project.manifest`;
  // const file = `${__dirname}/800f94fd-7424-4202-9629-d3ca77f3b72d.manifest`;
  res.download(file); // Set disposition and send it.
});

app.get('/assets/main/native/80/800f94fd-7424-4202-9629-d3ca77f3b72d.manifest', function(req, res){
  const file = `${__dirname}/800f94fd-7424-4202-9629-d3ca77f3b72d.manifest`;
  res.download(file); // Set disposition and send it.
});

// app.get('/assets/main/native/ae/ae4e2188-2b7b-42a9-85e1-8fb987600b04.png', function(req, res){
//   const file = `${__dirname}/Do99/res/bg.png`;
//   res.download(file); // Set disposition and send it.
// });

// app.get('/test', function (req, res) {
  // require('child_process').exec('start "" "E:\\codeTest\\expressjs\\cacao"');
// });

app.use('/remote-assets', express.static('./test/assets'))

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
})