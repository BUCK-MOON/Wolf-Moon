# generated from rosidl_generator_py/resource/_idl.py.em
# with input from ig_lio_c_msgs:srv/SaveMap.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SaveMap_Request(type):
    """Metaclass of message 'SaveMap_Request'."""

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
            module = import_type_support('ig_lio_c_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'ig_lio_c_msgs.srv.SaveMap_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__save_map__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__save_map__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__save_map__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__save_map__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__save_map__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SaveMap_Request(metaclass=Metaclass_SaveMap_Request):
    """Message class 'SaveMap_Request'."""

    __slots__ = [
        '_save_path',
        '_resolution',
    ]

    _fields_and_field_types = {
        'save_path': 'string',
        'resolution': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.save_path = kwargs.get('save_path', str())
        self.resolution = kwargs.get('resolution', float())

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
        if self.save_path != other.save_path:
            return False
        if self.resolution != other.resolution:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @property
    def save_path(self):
        """Message field 'save_path'."""
        return self._save_path

    @save_path.setter
    def save_path(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'save_path' field must be of type 'str'"
        self._save_path = value

    @property
    def resolution(self):
        """Message field 'resolution'."""
        return self._resolution

    @resolution.setter
    def resolution(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'resolution' field must be of type 'float'"
        self._resolution = value


# Import statements for member types

# already imported above
# import rosidl_parser.definition


class Metaclass_SaveMap_Response(type):
    """Metaclass of message 'SaveMap_Response'."""

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
            module = import_type_support('ig_lio_c_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'ig_lio_c_msgs.srv.SaveMap_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__save_map__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__save_map__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__save_map__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__save_map__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__save_map__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SaveMap_Response(metaclass=Metaclass_SaveMap_Response):
    """Message class 'SaveMap_Response'."""

    __slots__ = [
        '_status',
        '_message',
    ]

    _fields_and_field_types = {
        'status': 'int32',
        'message': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.status = kwargs.get('status', int())
        self.message = kwargs.get('message', str())

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
        if self.status != other.status:
            return False
        if self.message != other.message:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @property
    def status(self):
        """Message field 'status'."""
        return self._status

    @status.setter
    def status(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'status' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'status' field must be an integer in [-2147483648, 2147483647]"
        self._status = value

    @property
    def message(self):
        """Message field 'message'."""
        return self._message

    @message.setter
    def message(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'message' field must be of type 'str'"
        self._message = value


class Metaclass_SaveMap(type):
    """Metaclass of service 'SaveMap'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('ig_lio_c_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'ig_lio_c_msgs.srv.SaveMap')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__save_map

            from ig_lio_c_msgs.srv import _save_map
            if _save_map.Metaclass_SaveMap_Request._TYPE_SUPPORT is None:
                _save_map.Metaclass_SaveMap_Request.__import_type_support__()
            if _save_map.Metaclass_SaveMap_Response._TYPE_SUPPORT is None:
                _save_map.Metaclass_SaveMap_Response.__import_type_support__()


class SaveMap(metaclass=Metaclass_SaveMap):
    from ig_lio_c_msgs.srv._save_map import SaveMap_Request as Request
    from ig_lio_c_msgs.srv._save_map import SaveMap_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
