#!/bin/bash

FILE="addressbook.txt"

while true
do
    echo "=============================="
    echo "       ADDRESS BOOK"
    echo "=============================="
    echo "1. Create Address Book"
    echo "2. View Address Book"
    echo "3. Insert a Record"
    echo "4. Delete a Record"
    echo "5. Modify a Record"
    echo "6. Exit"
    echo "=============================="

    read -p "Enter your choice: " choice

    case $choice in

        1)
            # Create Address Book
            > "$FILE"
            echo "Address book created successfully."
            ;;

        2)
            # View Address Book
            if [ -s "$FILE" ]
            then
                echo "-------- ADDRESS BOOK --------"
                cat "$FILE"
            else
                echo "Address book is empty."
            fi
            ;;

        3)
            # Insert Record
            read -p "Enter Name: " name
            read -p "Enter Phone Number: " phone
            read -p "Enter Email: " email

            echo "$name | $phone | $email" >> "$FILE"

            echo "Record inserted successfully."
            ;;

        4)
            # Delete Record
            read -p "Enter Name to delete: " name

            if grep -q "^$name |" "$FILE"
            then
                grep -v "^$name |" "$FILE" > temp.txt
                mv temp.txt "$FILE"
                echo "Record deleted successfully."
            else
                echo "Record not found."
            fi
            ;;

        5)
            # Modify Record
            read -p "Enter Name to modify: " oldname

            if grep -q "^$oldname |" "$FILE"
            then
                read -p "Enter New Name: " newname
                read -p "Enter New Phone Number: " newphone
                read -p "Enter New Email: " newemail

                sed -i "s/^$oldname |.*/$newname | $newphone | $newemail/" "$FILE"

                echo "Record modified successfully."
            else
                echo "Record not found."
            fi
            ;;

        6)
            echo "Exiting Address Book..."
            exit 0
            ;;

        *)
            echo "Invalid choice. Please try again."
            ;;
    esac

    echo
done
