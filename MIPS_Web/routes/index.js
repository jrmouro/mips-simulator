var express = require('express');
const { v4: uuidv4 } = require('uuid');
var router = express.Router();

var getMipsframes = require("../frames");

/* GET home page. */
router.get('/', function (req, res, next) {

  if (req.session.frames_id) {

    if (!req.app.frames_session[req.session.frames_id]) {

      next(Error("no maped frame_id"));
      return;

    }

    var _frames = req.app.frames_session[req.session.frames_id];
    res.render(
      'index', 
      { 
        title: 'Express', 
        frame: _frames.self[_frames.current], 
        code: _frames.code, 
        current: _frames.current,
        length: _frames.self.length,
        mem_words: _frames.mem_words,
        max_clock: _frames.max_clock
      }
    );

  } else {

    req.session.frames_id = uuidv4();

    getMipsframes(req.session.frames_id, 16, "", 100)
      .then((frames) => {
        req.app.frames_session[req.session.frames_id] = frames;
        res.render(
          'index', 
          { 
            title: 'Express', 
            frame: frames.self[0], 
            code: frames.code, 
            current: frames.current,
            length: frames.self.length,
            mem_words: frames.mem_words,
            max_clock: frames.max_clock
          }
        );
      })
      .catch((rej) => {
        next(rej);
      });

  }

});

module.exports = router;
