import sys
import os
import platform

def create_desktop_shortcut(app_name, target_path, icon_path):
    system = platform.system()
    desktop_path = os.path.expanduser("~/Desktop")

    # ---------------------------------------------------------
    # 1. WINDOWS (Membuat file .lnk via Windows Script Host / VBScript)
    # ---------------------------------------------------------
    if system == "Windows":
        shortcut_path = os.path.join(desktop_path, f"{app_name}.lnk")
        vbs_script = f"""
        Set WshShell = CreateObject("WScript.Shell")
        Set shortcut = WshShell.CreateShortcut("{shortcut_path}")
        shortcut.TargetPath = "{target_path}"
        shortcut.IconLocation = "{icon_path}"
        shortcut.Save
        """
        vbs_path = "create_shortcut.vbs"
        with open(vbs_path, "w") as f:
            f.write(vbs_script)
        os.system(f'cscript //NoLogo "{vbs_path}"')
        os.remove(vbs_path)
        print(f"Shortcut Windows berhasil dibuat di: {shortcut_path}")

    # ---------------------------------------------------------
    # 2. LINUX (Membuat file .desktop)
    # ---------------------------------------------------------
    elif system == "Linux":
        shortcut_path = os.path.join(desktop_path, f"{app_name}.desktop")
        desktop_file_content = f"""[Desktop Entry]
Type=Application
Name={app_name}
Exec="{target_path}"
Icon={icon_path}
Terminal=false
"""
        with open(shortcut_path, "w") as f:
            f.write(desktop_file_content)
        
        # Beri izin eksekusi
        os.chmod(shortcut_path, 0o755)
        print(f"Shortcut Linux berhasil dibuat di: {shortcut_path}")