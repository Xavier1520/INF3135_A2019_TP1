tennis="examples/tennis"
compare="diff -ZB"

@test "Basic example runs with success" {
    run ./tournament < $tennis.in
    [ "$status" -eq 0 ]
}

@test "Wrong number of arguments" {
    run ./tournament -s < $tennis.in
    [ "$status" -eq 1 ]
    [ "$output" == "Error: wrong number of arguments" ]
}

@test "Short option for style is -s" {
    run ./tournament -s compact < $tennis.in
    [ "$status" -eq 0 ]
}

@test "Long option for format is --format" {
    run ./tournament --format id < $tennis.in
    [ "$status" -eq 0 ]
}

@test "Wrong option" {
    run ./tournament --sty compact < $tennis.in
    [ "$status" -eq 1 ]
    [ "$output" == "Error: unknown option (--sty)" ]
}

@test "Option recognition is case-sensitive" {
    run ./tournament --Style compact < $tennis.in
    [ "$status" -eq 1 ]
    [ "$output" == "Error: unknown option (--Style)" ]
}

@test "Wrong value for style" {
    run ./tournament --style compac < $tennis.in
    [ "$status" -eq 1 ]
    [ "$output" == "Error: unknown style (compac)" ]
}

@test "Wrong value for format" {
    run ./tournament --format ID < $tennis.in
    [ "$status" -eq 1 ]
    [ "$output" == "Error: unknown format (ID)" ]
}

@test "Tennis example with default options" {
    run $compare examples/tennis-default.out <(./tournament < examples/tennis.in)
    [ "$status" -eq 0 ]
}

@test "Soccer example with default options" {
    run $compare examples/soccer-default.out <(./tournament < examples/soccer.in)
    [ "$status" -eq 0 ]
}

@test "Tennis example with names" {
    run $compare examples/tennis-name.out <(./tournament -f name < examples/tennis.in)
    [ "$status" -eq 0 ]
}

@test "Tennis example with table" {
    run $compare examples/tennis-table.out <(./tournament -s table < examples/tennis.in)
    [ "$status" -eq 0 ]
}

@test "Tennis example with names in table" {
    run $compare examples/tennis-name-table.out <(./tournament -s table -f name < examples/tennis.in)
    [ "$status" -eq 0 ]
}

@test "Twenty players is ok" {
    head -n 20 examples/soccer-long.in | ./tournament
    [ "$?" -eq 0 ]
}

@test "Not enough players" {
    run ./tournament < examples/soccer-short.in
    [ "$output" == "Error: not enough players (minimum is 2)" ]
    [ "$status" -eq 1 ]
}

@test "Too many players" {
    run ./tournament < examples/soccer-long.in
    [ "$output" == "Error: too many players (maximum is 20)" ]
    [ "$status" -eq 1 ]
}

@test "Large table with id" {
    run $compare examples/soccer-long-table-id.out <(head -n 20 examples/soccer-long.in | ./tournament -s table)
    [ "$status" -eq 0 ]
}

@test "Large table with names" {
    run $compare examples/soccer-long-table-names.out <(head -n 20 examples/soccer-long.in | ./tournament -s table -f name)
    [ "$status" -eq 0 ]
}
