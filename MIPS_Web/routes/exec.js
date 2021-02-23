var express = require('express');
const { v4: uuidv4 } = require('uuid');
var router = express.Router();
var getMipsframes = require("../frames");

/* GET home page. */
router.post('/', function (req, res, next) {

  if(req.session.frames_id){

    if(!req.app.frames_session[req.session.frames_id]){

      next(Error("no maped frame_id"));
      return;

    }

    var code = req.body.code;
    var mem_size = req.body.inpt_mem_size;
    getMipsframes(req.session.frames_id, mem_size, code)
      .then((frames) => {        
        var current = frames.self.length - 1;
        req.app.frames_session[req.session.frames_id] = frames;
        req.app.frames_session[req.session.frames_id].current = current;
        res.render(
          'index', 
          { 
            title: 'Express', 
            frame: frames.self[current], 
            code: code, 
            current: current,
            length: frames.self.length,
            mem_words: frames.mem_words
          }
        );
      })
      .catch((rej) => {
        next(rej);
      });
   
  }else{

    res.redirect("/");

  }

});

module.exports = router;
