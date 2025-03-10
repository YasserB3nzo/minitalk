import re
import os

def fix_indentation(line):
    # Replace spaces at the beginning of the line with tabs
    # Assuming 4 spaces = 1 tab (common convention)
    spaces = len(line) - len(line.lstrip(' '))
    if spaces > 0:
        tabs = spaces // 4
        line = '\t' * tabs + line.lstrip(' ')
    return line

def fix_empty_line(line):
    # Remove spaces on empty lines
    if line.strip() == '':
        return ''
    return line

def fix_brace_eol(line):
    # Ensure that braces are followed by a newline
    if re.search(r'\{[^\n]*\}', line):
        line = re.sub(r'\{([^\n]*)\}', r'{\1\n', line)
    return line

def fix_file(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()

    fixed_lines = []
    for line in lines:
        line = fix_indentation(line)
        line = fix_empty_line(line)
        line = fix_brace_eol(line)
        fixed_lines.append(line)

    with open(file_path, 'w') as file:
        file.writelines(fixed_lines)

def fix_directory(directory):
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith('.c'):
                file_path = os.path.join(root, file)
                print(f'Fixing {file_path}')
                fix_file(file_path)

if __name__ == '__main__':
    directory = '.'  # Current directory, change if needed
    fix_directory(directory)