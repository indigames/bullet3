import os
import shutil
import platform

def setEnv(name, value):
    if platform.system() == 'Windows':
        os.system(f'set {name}={value}')
    else:
        os.system(f'export {name}={value}')
    os.environ[str(name)] = str(value)

def safeRemove(rm_path):
    try:
        if os.path.isfile(rm_path):
            os.remove(rm_path)
        else:
            shutil.rmtree(rm_path)
    except:
        pass

def build(platform, arch):
    safeRemove('build')
    os.mkdir('build')
    os.chdir('build')
    os.system(f'conan install --update .. --profile ../cmake/profiles/{platform}_{arch}')
    os.chdir('..')
    os.system('conan build . --build-folder build')

def main():
    setEnv('CONAN_REVISIONS_ENABLED', '1')
    if platform.system() == 'Windows':
        build('windows', 'x86')
        build('windows', 'x86_64')
        build('android', 'x86')
        build('android', 'x86_64')
        build('android', 'armv7')
        build('android', 'armv8')
    elif platform.system() == 'Darwin':
        build('macos', 'x86_64')
        build('ios', 'armv8')

if __name__ == "__main__":
    main()
