#!/bin/bash

ADDRESSBOOK_FILE="addressbook.txt"

create_addressbook() {
    if [ ! -f "$ADDRESSBOOK_FILE" ]; then
        touch "$ADDRESSBOOK_FILE"
        printf "%-10s %-20s %-15s %-30s\n" "RollNo" "Name" "Phone-Number" "Address" > "$ADDRESSBOOK_FILE"
        echo "Address book created successfully."
    else
        echo "Address book already exists."
    fi
}

insert_record() {
    # Validate Roll Number
    echo "RollNo (numeric, up to 5 digits):"
    read roll
    while [[ ! "$roll" =~ ^[0-9]{1,5}$ ]]; do
        echo "Invalid Roll Number. Please enter a numeric Roll Number up to 5 digits."
        read roll
    done

    # Validate Name
    echo "Name (letters only):"
    read name
    while [[ ! "$name" =~ ^[a-zA-Z]+$ ]]; do
        echo "Invalid Name. Please enter letters only."
        read name
    done

    # Validate Phone Number
    echo "Phone (10-digit):"
    read -r phone
    while [[ ! "$phone" =~ ^[0-9]{10}$ ]]; do
        echo "Please enter a valid 10-digit phone number:"
        read -r phone
    done

    # Validate Address
    echo "Address (up to 30 characters):"
    read address
    while [[ -z "$address" || ${#address} -gt 30 ]]; do
        echo "Invalid Address. Please enter a non-empty address up to 30 characters."
        read address
    done

    printf "%-10s %-20s %-15s %-30s\n" "$roll" "$name" "$phone" "$address" >> "$ADDRESSBOOK_FILE"
    echo "Record inserted successfully."
}

search_record() {
    echo "Enter the phone number to be searched:"
    read phon2
    if grep -q -w "$phon2" "$ADDRESSBOOK_FILE"; then
        grep -i -w "$phon2" "$ADDRESSBOOK_FILE"
        echo "Record found."
    else
        echo "Record not found."
    fi
}

delete_record() {
    echo "Enter the phone number to be deleted:"
    read phon
    if grep -q -w "$phon" "$ADDRESSBOOK_FILE"; then
        grep -v -i -w "$phon" "$ADDRESSBOOK_FILE" > temp.txt
        mv temp.txt "$ADDRESSBOOK_FILE"
        echo "Record deleted."
    else
        echo "Record not found."
    fi
}

modify_record() {
    echo "Enter the phone number to be modified:"
    read phon1
    if grep -q -w "$phon1" "$ADDRESSBOOK_FILE"; then
        old_record=$(grep -i -w "$phon1" "$ADDRESSBOOK_FILE")
        grep -v -i -w "$phon1" "$ADDRESSBOOK_FILE" > temp.txt
        mv temp.txt "$ADDRESSBOOK_FILE"
        echo "Old record: $old_record"
        echo "Please enter new details:"
        insert_record
        echo "Record modified successfully."
    else
        echo "Record not found."
    fi
}

while true; do
    echo "MENU
    1) Create address book
    2) View address book
    3) Insert a record
    4) Search a record
    5) Delete a record
    6) Modify a record
    7) Exit
    Enter your choice:"
    read choice

    case "$choice" in
        1) create_addressbook ;;
        2) cat "$ADDRESSBOOK_FILE" ;;
        3) insert_record ;;
        4) search_record ;;
        5) delete_record ;;
        6) modify_record ;;
        7) exit 0 ;;
        *) echo "Invalid choice, please try again." ;;
    esac
done
