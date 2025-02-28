# generated from rosidl_generator_py/resource/_idl.py.em
# with input from auto_aim_interfaces:msg/Uart.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Uart(type):
    """Metaclass of message 'Uart'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('auto_aim_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'auto_aim_interfaces.msg.Uart')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__uart
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__uart
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__uart
            cls._TYPE_SUPPORT = module.type_support_msg__msg__uart
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__uart

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Uart(metaclass=Metaclass_Uart):
    """Message class 'Uart'."""

    __slots__ = [
        '_header',
        '_remain_time',
        '_game_stage',
        '_outpost_hp',
        '_sentry_hp',
        '_commd_keyboard',
        '_x',
        '_y',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'remain_time': 'uint16',
        'game_stage': 'uint8',
        'outpost_hp': 'uint16',
        'sentry_hp': 'uint16',
        'commd_keyboard': 'uint8',
        'x': 'uint8',
        'y': 'uint8',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.remain_time = kwargs.get('remain_time', int())
        self.game_stage = kwargs.get('game_stage', int())
        self.outpost_hp = kwargs.get('outpost_hp', int())
        self.sentry_hp = kwargs.get('sentry_hp', int())
        self.commd_keyboard = kwargs.get('commd_keyboard', int())
        self.x = kwargs.get('x', int())
        self.y = kwargs.get('y', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.header != other.header:
            return False
        if self.remain_time != other.remain_time:
            return False
        if self.game_stage != other.game_stage:
            return False
        if self.outpost_hp != other.outpost_hp:
            return False
        if self.sentry_hp != other.sentry_hp:
            return False
        if self.commd_keyboard != other.commd_keyboard:
            return False
        if self.x != other.x:
            return False
        if self.y != other.y:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if __debug__:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

    @property
    def remain_time(self):
        """Message field 'remain_time'."""
        return self._remain_time

    @remain_time.setter
    def remain_time(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'remain_time' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'remain_time' field must be an unsigned integer in [0, 65535]"
        self._remain_time = value

    @property
    def game_stage(self):
        """Message field 'game_stage'."""
        return self._game_stage

    @game_stage.setter
    def game_stage(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'game_stage' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'game_stage' field must be an unsigned integer in [0, 255]"
        self._game_stage = value

    @property
    def outpost_hp(self):
        """Message field 'outpost_hp'."""
        return self._outpost_hp

    @outpost_hp.setter
    def outpost_hp(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'outpost_hp' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'outpost_hp' field must be an unsigned integer in [0, 65535]"
        self._outpost_hp = value

    @property
    def sentry_hp(self):
        """Message field 'sentry_hp'."""
        return self._sentry_hp

    @sentry_hp.setter
    def sentry_hp(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'sentry_hp' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'sentry_hp' field must be an unsigned integer in [0, 65535]"
        self._sentry_hp = value

    @property
    def commd_keyboard(self):
        """Message field 'commd_keyboard'."""
        return self._commd_keyboard

    @commd_keyboard.setter
    def commd_keyboard(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'commd_keyboard' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'commd_keyboard' field must be an unsigned integer in [0, 255]"
        self._commd_keyboard = value

    @property
    def x(self):
        """Message field 'x'."""
        return self._x

    @x.setter
    def x(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'x' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'x' field must be an unsigned integer in [0, 255]"
        self._x = value

    @property
    def y(self):
        """Message field 'y'."""
        return self._y

    @y.setter
    def y(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'y' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'y' field must be an unsigned integer in [0, 255]"
        self._y = value
