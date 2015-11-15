;; Auto-generated. Do not edit!


(when (boundp 'sound_play::SoundRequest)
  (if (not (find-package "SOUND_PLAY"))
    (make-package "SOUND_PLAY"))
  (shadow 'SoundRequest (find-package "SOUND_PLAY")))
(unless (find-package "SOUND_PLAY::SOUNDREQUEST")
  (make-package "SOUND_PLAY::SOUNDREQUEST"))

(in-package "ROS")
;;//! \htmlinclude SoundRequest.msg.html


(intern "*BACKINGUP*" (find-package "SOUND_PLAY::SOUNDREQUEST"))
(shadow '*BACKINGUP* (find-package "SOUND_PLAY::SOUNDREQUEST"))
(defconstant sound_play::SoundRequest::*BACKINGUP* 1)
(intern "*NEEDS_UNPLUGGING*" (find-package "SOUND_PLAY::SOUNDREQUEST"))
(shadow '*NEEDS_UNPLUGGING* (find-package "SOUND_PLAY::SOUNDREQUEST"))
(defconstant sound_play::SoundRequest::*NEEDS_UNPLUGGING* 2)
(intern "*NEEDS_PLUGGING*" (find-package "SOUND_PLAY::SOUNDREQUEST"))
(shadow '*NEEDS_PLUGGING* (find-package "SOUND_PLAY::SOUNDREQUEST"))
(defconstant sound_play::SoundRequest::*NEEDS_PLUGGING* 3)
(intern "*NEEDS_UNPLUGGING_BADLY*" (find-package "SOUND_PLAY::SOUNDREQUEST"))
(shadow '*NEEDS_UNPLUGGING_BADLY* (find-package "SOUND_PLAY::SOUNDREQUEST"))
(defconstant sound_play::SoundRequest::*NEEDS_UNPLUGGING_BADLY* 4)
(intern "*NEEDS_PLUGGING_BADLY*" (find-package "SOUND_PLAY::SOUNDREQUEST"))
(shadow '*NEEDS_PLUGGING_BADLY* (find-package "SOUND_PLAY::SOUNDREQUEST"))
(defconstant sound_play::SoundRequest::*NEEDS_PLUGGING_BADLY* 5)
(intern "*ALL*" (find-package "SOUND_PLAY::SOUNDREQUEST"))
(shadow '*ALL* (find-package "SOUND_PLAY::SOUNDREQUEST"))
(defconstant sound_play::SoundRequest::*ALL* -1)
(intern "*PLAY_FILE*" (find-package "SOUND_PLAY::SOUNDREQUEST"))
(shadow '*PLAY_FILE* (find-package "SOUND_PLAY::SOUNDREQUEST"))
(defconstant sound_play::SoundRequest::*PLAY_FILE* -2)
(intern "*SAY*" (find-package "SOUND_PLAY::SOUNDREQUEST"))
(shadow '*SAY* (find-package "SOUND_PLAY::SOUNDREQUEST"))
(defconstant sound_play::SoundRequest::*SAY* -3)
(intern "*PLAY_STOP*" (find-package "SOUND_PLAY::SOUNDREQUEST"))
(shadow '*PLAY_STOP* (find-package "SOUND_PLAY::SOUNDREQUEST"))
(defconstant sound_play::SoundRequest::*PLAY_STOP* 0)
(intern "*PLAY_ONCE*" (find-package "SOUND_PLAY::SOUNDREQUEST"))
(shadow '*PLAY_ONCE* (find-package "SOUND_PLAY::SOUNDREQUEST"))
(defconstant sound_play::SoundRequest::*PLAY_ONCE* 1)
(intern "*PLAY_START*" (find-package "SOUND_PLAY::SOUNDREQUEST"))
(shadow '*PLAY_START* (find-package "SOUND_PLAY::SOUNDREQUEST"))
(defconstant sound_play::SoundRequest::*PLAY_START* 2)
(defclass sound_play::SoundRequest
  :super ros::object
  :slots (_sound _command _arg _arg2 ))

(defmethod sound_play::SoundRequest
  (:init
   (&key
    ((:sound __sound) 0)
    ((:command __command) 0)
    ((:arg __arg) "")
    ((:arg2 __arg2) "")
    )
   (send-super :init)
   (setq _sound (round __sound))
   (setq _command (round __command))
   (setq _arg (string __arg))
   (setq _arg2 (string __arg2))
   self)
  (:sound
   (&optional __sound)
   (if __sound (setq _sound __sound)) _sound)
  (:command
   (&optional __command)
   (if __command (setq _command __command)) _command)
  (:arg
   (&optional __arg)
   (if __arg (setq _arg __arg)) _arg)
  (:arg2
   (&optional __arg2)
   (if __arg2 (setq _arg2 __arg2)) _arg2)
  (:serialization-length
   ()
   (+
    ;; int8 _sound
    1
    ;; int8 _command
    1
    ;; string _arg
    4 (length _arg)
    ;; string _arg2
    4 (length _arg2)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _sound
       (write-byte _sound s)
     ;; int8 _command
       (write-byte _command s)
     ;; string _arg
       (write-long (length _arg) s) (princ _arg s)
     ;; string _arg2
       (write-long (length _arg2) s) (princ _arg2 s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _sound
     (setq _sound (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _sound 127) (setq _sound (- _sound 256)))
   ;; int8 _command
     (setq _command (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _command 127) (setq _command (- _command 256)))
   ;; string _arg
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _arg (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; string _arg2
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _arg2 (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(setf (get sound_play::SoundRequest :md5sum-) "f194e75f1c3bf7a3e1e8b16bc9ef7c2a")
(setf (get sound_play::SoundRequest :datatype-) "sound_play/SoundRequest")
(setf (get sound_play::SoundRequest :definition-)
      "# IMPORTANT: You should never have to generate this message yourself.
# Use the sound_play::SoundClient C++ helper or the
# sound_play.libsoundplay.SoundClient Python helper.

# Sounds
int8 BACKINGUP = 1
int8 NEEDS_UNPLUGGING = 2
int8 NEEDS_PLUGGING = 3
int8 NEEDS_UNPLUGGING_BADLY = 4
int8 NEEDS_PLUGGING_BADLY = 5

# Sound identifiers that have special meaning
int8 ALL = -1 # Only legal with PLAY_STOP
int8 PLAY_FILE = -2
int8 SAY = -3

int8 sound # Selects which sound to play (see above)

# Commands
int8 PLAY_STOP = 0 # Stop this sound from playing
int8 PLAY_ONCE = 1 # Play the sound once
int8 PLAY_START = 2 # Play the sound in a loop until a stop request occurs

int8 command # Indicates what to do with the sound

string arg # file name or text to say
string arg2 # other arguments

")



(provide :sound_play/SoundRequest "f194e75f1c3bf7a3e1e8b16bc9ef7c2a")


