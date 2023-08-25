# Ultrahand Overlay (HOS 16.0.0+)
![Overlay Menu](https://gbatemp.net/attachments/img_4543-jpg.386203/)
![Package Menu](https://gbatemp.net/attachments/img_4547-jpg.386207/)
![Broomstick Package](https://gbatemp.net/attachments/img_4544-jpg.386202/)
![Mod Master Package](https://gbatemp.net/attachments/img_4546-jpg.386206/)
![Easy Installer Package](https://gbatemp.net/attachments/img_4545-jpg.386208/)

Craft, Share, and Customize Your Commands!

Ultrahand is a versatile tool that enables you to create and share packages, providing enhanced functionality for managing files and directories on your SD card. It offers a range of features that allow you to efficiently interact with your system environment. With Ultrahand, you have the flexibility to customize and shape your file management system according to your needs, empowering you with greater control over your configurations.

Create directories, merge files, and customize configurations effortlessly using simple config.ini files.

## Features

Ultrahand is a Tesla overlay that provides powerful functionality for managing files and directories on an SD card. It offers the following features:

- Create Directories:
  - Effortlessly create directories on your SD card by specifying the directory path. Ultrahand will handle the creation process for you.

- Copy Files or Directories:
  - Easily copy files or directories from one location to another on your SD card. Just provide the source and destination paths, and Ultrahand will seamlessly handle the copying process.

- Delete Files or Directories:
  - Simplify file and directory deletion on your SD card. By specifying the path of the file or directory you want to delete, Ultrahand promptly removes it, making the deletion process hassle-free.

- Move Files or Directories:
  - Seamlessly move files or directories between locations on your SD card. Provide the source path and the destination directory path, and Ultrahand takes care of the moving process, ensuring smooth relocation.

- Modify INI Files:
  - Edit INI files on your SD card with ease. Take full control over your configurations by updating existing key-value pairs, adding new entries, or creating new sections within the INI file using Ultrahand. Customize and tailor your INI files effortlessly through its intuitive interface.

- Hex Edit Files:
  - Perform hexadecimal editing of files on your SD card. Edit the binary data directly, allowing for precise control over your data. Ultrahand's Hex Edit Files feature enables you to analyze, modify, and customize files in their raw form.

Ultrahand provides a convenient command-line interface to perform these operations, allowing you to efficiently manage your files, directories, and INI files on an SD card.


## Getting Started

### Nintendo Switch Compatibility
To run the Ultrahand File Management overlay on the Nintendo Switch, you need to have the necessary homebrew environment set up on your console. Once you have the homebrew environment set up, you can transfer the compiled executable file to your Switch and launch it using the Tesla Overlay.

Please note that running homebrew software on your Nintendo Switch may void your warranty and can carry certain risks. Ensure that you understand the implications and follow the appropriate guidelines and precautions when using homebrew software.

### Compilation Prerequisites

To compile and run the program, you need to have the following dependencies installed:

- TESLA library
- Standard C++ libraries


### Usage

To use Ultrahand, follow these steps:

1. Create a directory named ultrahand in the config root folder on your SD card.
2. Place the config.ini package file in the ultrahand directory (or sub-directory). This package file contains the configuration options for Ultrahand.
3. Your commands will show up on the Tesla menu within the Ultrahand overlay.  You can click A to execute any command as well as click X to view the indivicual command lines written in the ini for execution.

## Configuration Options

The config.ini file contains multiple sections, each defining a set of commands that can be executed. The sections are enclosed in square brackets [ ], and the commands are listed below each section.

Here's an example of the config.ini file:
```
[make directories]
mkdir /switch/.packages/example1/
mkdir /switch/.packages/example2/

[copy files]
copy /switch/.packages/config.ini /switch/.packages/example1/
copy /switch/.packages/config.ini /switch/.packages/example2/

[rename files]
move /switch/.packages/example1/config.ini /switch/.packages/example1/configX.ini
move /switch/.packages/example2/config.ini /switch/.packages/example2/configX.ini

[move directories]
move /switch/.packages/example1/ /switch/.packages/example3/
move /switch/.packages/example2/ /switch/.packages/example4/

[delete files]
delete /switch/.packages/example1/config.ini
delete /switch/.packages/example2/config.ini

[delete directories]
delete /switch/.packages/example1/
delete /switch/.packages/example2/
delete /switch/.packages/example3/
delete /switch/.packages/example4/

[modify ini file]
copy /bootloader/hekate_ipl.ini /switch/.packages/
set-ini-val /switch/.packages/hekate_ipl.ini 'Atmosphere' fss0 gonnawritesomethingelse
set-ini-val ​/switch/.packages/hekate_ipl.ini 'Atmosphere' booty true
```
You can add your own sections and commands to customize the actions performed by Ultrahand.

Note: The paths specified in the commands should be relative to the SD card root directory and should end with /.

## Command Reference

Ultrahand supports the following commands:

- make or mkdir: Creates a directory.
  - Usage: `mkdir <directory_path>`

- copy or cp: Copies a file or diectory.
  - Usage: `copy <source_file_path> <destination_file_path>`

- delete or del: Deletes a file or directory.
  - Usage: `delete <file_path>`

- move or mv: Moves/renames a file/directory to a new location/label.
  - Usage: `move <file_path> <destination_directory_path>`

- set-ini-val or set-ini-value: Edits an INI file by updating (or adding) a section with a desired key-value pair.
  - Usage: `set-ini-val <file_to_edit> <desired_section> <desired_key> <desired_value>`

- set-ini-key: Edits an INI file by updating a section with a new key.
  - Usage: `set-ini-key <file_to_edit> <desired_section> <desired_key> <desired_new_key>`

- hex-by-offset: Edits the contents of a file at a specified offset with the provided hexadecimal data.
  - Usage: `hex-by-offset <file_path> <offset> <hex_data>`

- hex-by-swap: Edits the contents of a file by replacing a specified hexadecimal data with another.
  - Usage: `hex-by-swap <file_path> <hex_data_to_replace> <hex_data_replacement>`
  
- hex-by-decimal: Edits the contents of a file by replacing a specified decimal data with another.
  - Usage: `hex-by-decimal <file_path> <decimal_data_to_replace> <decimal_data_replacement>`
  
- hex-by-rdecimal: Edits the contents of a file by replacing a specified reverse decimal data with another.
  - Usage: `hex-by-rdecimal <file_path> <decimal_data_to_replace> <decimal_data_replacement>`

- hex-by-string: Edits the contents of a file by replacing a specified string data with another.
  - Usage: `hex-by-string <file_path> <string_data_to_replace> <string_data_replacement>`

- hex-by-cust-offset: Changes the value with offset from the word CUST in loader.kip. 
  - Usage: `hex-by-cust-offset <kip_path> <offset> <string_data_replacement>`

- reboot: Restarts the system.
  - Usage: `reboot`

- shutdown: Shuts down the system.
  - Usage: `shutdown`


Make sure to follow the correct syntax and provide the required arguments for each command.

You can configure these commands in the `config.ini` file by specifying them under the corresponding options. Make sure to provide the necessary arguments as described for each command.


## Contributing

Contributions are welcome! If you have any ideas, suggestions, or bug reports, please create an issue or submit a pull request.

## License

This project is licensed under the [CC-BY-NC-4.0 License](LICENSE).

