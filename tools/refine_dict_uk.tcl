# Load the Unix-like system dictionary and eliminate all the words that have
# capital letters, or have hyphens, or have less than 3 chars (with apostrophes
# excluded), or have more than 7 chars (with apostrophes excluded).
# If a word has apostrophes, keep it with the apostrophes discarded.
# Encode the suitable entries with the alphabet composed of ASCII characters.

proc delete_char {text position} {
  set lead [string range $text 0 [expr {$position - 1}]]
  set trail [string range $text [expr {$position + 1}] \
    [expr {[string length $text] - 1}]]

  return [format "%s%s" $lead $trail]
}

proc encode {text src dest} {
  set pos 0
  while {[set init_ch [string index $src $pos]] != "" && \
    [set fin_ch [string index $dest $pos]] != ""} {
    while {[set res [regsub $init_ch $text $fin_ch text]] != 0} {
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

  set init_ab "абвгґдеєжзиіїйклмнопрстуфхцчшщьюя"
  set fin_ab "f,du\\lt';pbs]qrkvyjghcnea\[wxiom.z"

  while {[set len [gets $f word]] != -1} {
    # Discard apostrophes.
    while {[set ind [string first "'" $word]] != -1} {
      set word [delete_char $word $ind]
      incr len -1
    }

    # Prune out the undesirable entries.
    if {$len > 7 || $len < 3 || [string first "-" $word] != -1 || \
      $word ne [string tolower $word]} {
      puts stderr "Skip \"$word\"."
      continue
    }

    # Encode entries.
    set word [encode $word $init_ab $fin_ab]

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
