from distutils.core import setup, Extension


def main():
    setup(
        name='pyikfast',
        version='0.0.1',
        description='ikfast wrapper',
        author='Cyberbotics',
        author_email='support@cyberbotics.com',
        ext_modules=[Extension('pyikfast', ['ikfast0x1000004a.Transform6D.0_1_2_3_4_5.cpp', 'pyikfast.cpp'])]
    )


if __name__ == '__main__':
    main()
