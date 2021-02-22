var express = require('express');
const { v4: uuidv4 } = require('uuid');
var router = express.Router();

var frames = require("../frames");

/* GET home page. */
router.get('/', function (req, res, next) {

  console.log(req.session);

  if(req.session.frames_id){

    if(req.app.frames_session[req.session.frames_id]){

      var _frame = req.app.frames_session[req.session.frames_id].get_first_frame();

      res.render('index', { title: 'Express' , frame: _frame});

      console.log("frames_session[" + req.session.frames_id + "]: " + req.app.frames_session[req.session.frames_id]);


    }else{

      next(Error("no maped frame_id"));

    }
    
  }else{

    req.session.frames_id = uuidv4();
    req.app.frames_session[req.session.frames_id] = new frames(req.session.frames_id);
    console.log(req.app.frames_session);
    console.log(req.app.frames_session[req.session.frames_id]);

  }

  res.render('index', { title: 'Express' });

});

module.exports = router;
