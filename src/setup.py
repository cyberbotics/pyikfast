from distutils.core import setup, Extension


def main():
    setup(
        name='pyikfast[put_extension]',
        version='0.0.1',
        description='ikfast wrapper',
        author='Cyberbotics',
        author_email='support@cyberbotics.com',
        ext_modules=[Extension('pyikfast', ['ikfast_robot.cpp', 'pyikfast.cpp'])]
    )


if __name__ == '__main__':
    main()
