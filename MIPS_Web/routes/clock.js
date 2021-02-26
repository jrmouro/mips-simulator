var express = require('express');
const { v4: uuidv4 } = require('uuid');
var router = express.Router();
var getMipsframes = require("../frames");

/* GET home page. */
router.post('/', function (req, res, next) {

  if (req.session.frames_id) {

    if (!req.app.frames_session[req.session.frames_id]) {

      next(Error("no maped frame_id"));
      return;

    }

    var code = req.body.code;
    var mem_size = req.body.inpt_mem_size;

    if (req.app.frames_session[req.session.frames_id].code != code ||
      req.app.frames_session[req.session.frames_id].mem_words != mem_size) {

      
      getMipsframes(req.session.frames_id, mem_size, code)
        .then((frames) => {
          var current = 0;
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

        return;

    }

    var current = req.app.frames_session[req.session.frames_id].current+1;
    if (current < req.app.frames_session[req.session.frames_id].self.length) {
      req.app.frames_session[req.session.frames_id].current = current;
    }else{
      current--;
    }

    res.render(
      'index',
      {
        title: 'Express',
        frame: req.app.frames_session[req.session.frames_id].self[current],
        code: code,
        current: current,
        length: req.app.frames_session[req.session.frames_id].self.length,
        mem_words: req.app.frames_session[req.session.frames_id].mem_words
      }
    );

  } else {

    res.redirect('/');

  }

  console.log("xxxxxxxxxxxxxx");

});

module.exports = router;