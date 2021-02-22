var express = require('express');
const { v4: uuidv4 } = require('uuid');
var router = express.Router();

var frames = require("../frames");

/* GET home page. */
router.get('/', function (req, res, next) {

    res.render('index2', { title: 'Express' });

});

module.exports = router;
