# Transform the given entries in a reversible way so that they match
# another alphabet.

proc transform {text src temp dest} {
  set pos 0
  while {[set init_ch [string index $src $pos]] != "" && \
    [set aux_ch [string index $temp $pos]] != ""} {
    while {[set res [regsub $init_ch $text $aux_ch text]] != 0} {
      # puts "$res0, $text"
    }
    incr pos 1
  }

  set pos 0
  while {[set aux_ch [string index $temp $pos]] != "" && \
    [set fin_ch [string index $dest $pos]] != ""} {
    while {[set res [regsub $aux_ch $text $fin_ch text]] != 0} {
      # puts "$res, $text"
    }
    incr pos 1
  }

  return $text
}

proc main {filename} {
  # Read the dictionary file.
  set f [open $filename r]
  fconfigure $f -encoding utf-8

  set init_ab "amqwz"
  set aux_ab "01234"
  set fin_ab "q;azw"

  while {[set len [gets $f word]] != -1} {
    # Transform entries.
    set word [transform $word $init_ab $aux_ab $fin_ab]

    puts $word
  }

  close $f
}

if {!$tcl_interactive} {
  set r [catch [linsert $argv 0 main] err]
  if {$r} {puts $errorInfo}
  exit $r
}

# Local variables:
# mode: tcl
# indent-tabs-mode: nil
# tab-width: 2
# End:
