var express = require('express');
const { v4: uuidv4 } = require('uuid');
var router = express.Router();

/* GET home page. */
router.post('/', function (req, res, next) {

  console.log(req.session);

  if(req.session.frames_id){

    if(req.app.frames_session[req.session.frames_id]){

      if(req.app.frames_session[req.session.frames_id] === "no_frames_yet"){


      }else{


      }

      console.log("frames_session[" + req.session.frames_id + "]: " + req.app.frames_session[req.session.frames_id]);


    }else{

      next(Error("no maped frame_id"));

    }
    
  }else{
    req.session.frames_id = uuidv4();
    req.app.frames_session[req.session.frames_id] = "no_frames_yet";
    console.log(req.app.frames_session);
  }

  res.render('index', { title: 'Express' });

});

module.exports = router;
