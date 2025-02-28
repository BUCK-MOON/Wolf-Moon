# generated from rosidl_generator_py/resource/_idl.py.em
# with input from auto_aim_interfaces:msg/State.idl
# generated code does not contain a copyright notice


# Import statements for member types

# Member 'state'
import numpy  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_State(type):
    """Metaclass of message 'State'."""

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
                'auto_aim_interfaces.msg.State')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__state
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__state
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__state
            cls._TYPE_SUPPORT = module.type_support_msg__msg__state
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__state

            from auto_aim_interfaces.msg import Point2f
            if Point2f.__class__._TYPE_SUPPORT is None:
                Point2f.__class__.__import_type_support__()

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


class State(metaclass=Metaclass_State):
    """Message class 'State'."""

    __slots__ = [
        '_header',
        '_mode',
        '_center',
        '_predict',
        '_calculate',
        '_angle',
        '_state',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'mode': 'uint8',
        'center': 'auto_aim_interfaces/Point2f[4]',
        'predict': 'auto_aim_interfaces/Point2f',
        'calculate': 'auto_aim_interfaces/Point2f',
        'angle': 'auto_aim_interfaces/Point2f',
        'state': 'double[9]',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.NamespacedType(['auto_aim_interfaces', 'msg'], 'Point2f'), 4),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['auto_aim_interfaces', 'msg'], 'Point2f'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['auto_aim_interfaces', 'msg'], 'Point2f'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['auto_aim_interfaces', 'msg'], 'Point2f'),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('double'), 9),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.mode = kwargs.get('mode', int())
        from auto_aim_interfaces.msg import Point2f
        self.center = kwargs.get(
            'center',
            [Point2f() for x in range(4)]
        )
        from auto_aim_interfaces.msg import Point2f
        self.predict = kwargs.get('predict', Point2f())
        from auto_aim_interfaces.msg import Point2f
        self.calculate = kwargs.get('calculate', Point2f())
        from auto_aim_interfaces.msg import Point2f
        self.angle = kwargs.get('angle', Point2f())
        if 'state' not in kwargs:
            self.state = numpy.zeros(9, dtype=numpy.float64)
        else:
            self.state = numpy.array(kwargs.get('state'), dtype=numpy.float64)
            assert self.state.shape == (9, )

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
        if self.mode != other.mode:
            return False
        if self.center != other.center:
            return False
        if self.predict != other.predict:
            return False
        if self.calculate != other.calculate:
            return False
        if self.angle != other.angle:
            return False
        if all(self.state != other.state):
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
    def mode(self):
        """Message field 'mode'."""
        return self._mode

    @mode.setter
    def mode(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'mode' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'mode' field must be an unsigned integer in [0, 255]"
        self._mode = value

    @property
    def center(self):
        """Message field 'center'."""
        return self._center

    @center.setter
    def center(self, value):
        if __debug__:
            from auto_aim_interfaces.msg import Point2f
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 4 and
                 all(isinstance(v, Point2f) for v in value) and
                 True), \
                "The 'center' field must be a set or sequence with length 4 and each value of type 'Point2f'"
        self._center = value

    @property
    def predict(self):
        """Message field 'predict'."""
        return self._predict

    @predict.setter
    def predict(self, value):
        if __debug__:
            from auto_aim_interfaces.msg import Point2f
            assert \
                isinstance(value, Point2f), \
                "The 'predict' field must be a sub message of type 'Point2f'"
        self._predict = value

    @property
    def calculate(self):
        """Message field 'calculate'."""
        return self._calculate

    @calculate.setter
    def calculate(self, value):
        if __debug__:
            from auto_aim_interfaces.msg import Point2f
            assert \
                isinstance(value, Point2f), \
                "The 'calculate' field must be a sub message of type 'Point2f'"
        self._calculate = value

    @property
    def angle(self):
        """Message field 'angle'."""
        return self._angle

    @angle.setter
    def angle(self, value):
        if __debug__:
            from auto_aim_interfaces.msg import Point2f
            assert \
                isinstance(value, Point2f), \
                "The 'angle' field must be a sub message of type 'Point2f'"
        self._angle = value

    @property
    def state(self):
        """Message field 'state'."""
        return self._state

    @state.setter
    def state(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.float64, \
                "The 'state' numpy.ndarray() must have the dtype of 'numpy.float64'"
            assert value.size == 9, \
                "The 'state' numpy.ndarray() must have a size of 9"
            self._state = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 9 and
                 all(isinstance(v, float) for v in value) and
                 True), \
                "The 'state' field must be a set or sequence with length 9 and each value of type 'float'"
        self._state = numpy.array(value, dtype=numpy.float64)
