/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../v1/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[113];
    char stringdata0[2731];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 4), // "Init"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 11), // "QuitProgram"
QT_MOC_LITERAL(4, 29, 16), // "InterruptTimeout"
QT_MOC_LITERAL(5, 46, 21), // "Program_the_digitizer"
QT_MOC_LITERAL(6, 68, 7), // "Restart"
QT_MOC_LITERAL(7, 76, 17), // "Mask_the_channels"
QT_MOC_LITERAL(8, 94, 12), // "Readout_loop"
QT_MOC_LITERAL(9, 107, 16), // "StopReadout_loop"
QT_MOC_LITERAL(10, 124, 17), // "ContinuousTrigger"
QT_MOC_LITERAL(11, 142, 15), // "ContinuousWrite"
QT_MOC_LITERAL(12, 158, 15), // "SetRecordLength"
QT_MOC_LITERAL(13, 174, 5), // "value"
QT_MOC_LITERAL(14, 180, 11), // "TestPattern"
QT_MOC_LITERAL(15, 192, 20), // "EnableContinuousPlot"
QT_MOC_LITERAL(16, 213, 21), // "DisableContinuousPlot"
QT_MOC_LITERAL(17, 235, 11), // "MaskChannel"
QT_MOC_LITERAL(18, 247, 15), // "SetTriggerValue"
QT_MOC_LITERAL(19, 263, 14), // "MaskChannelAll"
QT_MOC_LITERAL(20, 278, 22), // "CHANNEL_TRIGGER_signal"
QT_MOC_LITERAL(21, 301, 19), // "CHANNEL_TRIGGER_all"
QT_MOC_LITERAL(22, 321, 14), // "SetOutFileType"
QT_MOC_LITERAL(23, 336, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(24, 358, 25), // "on_radioButton_13_clicked"
QT_MOC_LITERAL(25, 384, 25), // "on_radioButton_12_clicked"
QT_MOC_LITERAL(26, 410, 19), // "on_checkBox_clicked"
QT_MOC_LITERAL(27, 430, 25), // "on_spinBox_3_valueChanged"
QT_MOC_LITERAL(28, 456, 4), // "arg1"
QT_MOC_LITERAL(29, 461, 29), // "on_doubleSpinBox_valueChanged"
QT_MOC_LITERAL(30, 491, 31), // "on_doubleSpinBox_2_valueChanged"
QT_MOC_LITERAL(31, 523, 25), // "on_spinBox_4_valueChanged"
QT_MOC_LITERAL(32, 549, 25), // "on_radioButton_15_clicked"
QT_MOC_LITERAL(33, 575, 7), // "checked"
QT_MOC_LITERAL(34, 583, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(35, 607, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(36, 631, 21), // "on_groupBox_3_clicked"
QT_MOC_LITERAL(37, 653, 28), // "on_spinBox_4_editingFinished"
QT_MOC_LITERAL(38, 682, 30), // "on_Test_Pattern_button_clicked"
QT_MOC_LITERAL(39, 713, 23), // "on_pushButton_5_clicked"
QT_MOC_LITERAL(40, 737, 23), // "on_pushButton_4_clicked"
QT_MOC_LITERAL(41, 761, 22), // "on_checkBox_11_clicked"
QT_MOC_LITERAL(42, 784, 22), // "on_checkBox_12_clicked"
QT_MOC_LITERAL(43, 807, 22), // "on_checkBox_13_clicked"
QT_MOC_LITERAL(44, 830, 22), // "on_checkBox_14_clicked"
QT_MOC_LITERAL(45, 853, 22), // "on_checkBox_15_clicked"
QT_MOC_LITERAL(46, 876, 22), // "on_checkBox_21_clicked"
QT_MOC_LITERAL(47, 899, 22), // "on_checkBox_22_clicked"
QT_MOC_LITERAL(48, 922, 22), // "on_checkBox_23_clicked"
QT_MOC_LITERAL(49, 945, 30), // "on_verticalSlider_valueChanged"
QT_MOC_LITERAL(50, 976, 25), // "on_spinBox_2_valueChanged"
QT_MOC_LITERAL(51, 1002, 23), // "on_pushButton_6_clicked"
QT_MOC_LITERAL(52, 1026, 31), // "on_pushButton_Reprogram_clicked"
QT_MOC_LITERAL(53, 1058, 22), // "on_checkBox_24_clicked"
QT_MOC_LITERAL(54, 1081, 22), // "on_checkBox_25_clicked"
QT_MOC_LITERAL(55, 1104, 22), // "on_checkBox_31_clicked"
QT_MOC_LITERAL(56, 1127, 22), // "on_checkBox_32_clicked"
QT_MOC_LITERAL(57, 1150, 22), // "on_checkBox_33_clicked"
QT_MOC_LITERAL(58, 1173, 22), // "on_checkBox_34_clicked"
QT_MOC_LITERAL(59, 1196, 22), // "on_checkBox_35_clicked"
QT_MOC_LITERAL(60, 1219, 22), // "on_checkBox_41_clicked"
QT_MOC_LITERAL(61, 1242, 22), // "on_checkBox_42_clicked"
QT_MOC_LITERAL(62, 1265, 22), // "on_checkBox_43_clicked"
QT_MOC_LITERAL(63, 1288, 22), // "on_checkBox_44_clicked"
QT_MOC_LITERAL(64, 1311, 22), // "on_checkBox_45_clicked"
QT_MOC_LITERAL(65, 1334, 22), // "on_checkBox_51_clicked"
QT_MOC_LITERAL(66, 1357, 22), // "on_checkBox_52_clicked"
QT_MOC_LITERAL(67, 1380, 22), // "on_checkBox_53_clicked"
QT_MOC_LITERAL(68, 1403, 22), // "on_checkBox_54_clicked"
QT_MOC_LITERAL(69, 1426, 22), // "on_checkBox_55_clicked"
QT_MOC_LITERAL(70, 1449, 23), // "on_pushButton_7_clicked"
QT_MOC_LITERAL(71, 1473, 23), // "on_pushButton_8_clicked"
QT_MOC_LITERAL(72, 1497, 38), // "on_CHANNEL_TRIGGER_checkBox_1..."
QT_MOC_LITERAL(73, 1536, 38), // "on_CHANNEL_TRIGGER_checkBox_1..."
QT_MOC_LITERAL(74, 1575, 38), // "on_CHANNEL_TRIGGER_checkBox_1..."
QT_MOC_LITERAL(75, 1614, 38), // "on_CHANNEL_TRIGGER_checkBox_1..."
QT_MOC_LITERAL(76, 1653, 38), // "on_CHANNEL_TRIGGER_checkBox_1..."
QT_MOC_LITERAL(77, 1692, 38), // "on_CHANNEL_TRIGGER_checkBox_2..."
QT_MOC_LITERAL(78, 1731, 38), // "on_CHANNEL_TRIGGER_checkBox_2..."
QT_MOC_LITERAL(79, 1770, 38), // "on_CHANNEL_TRIGGER_checkBox_2..."
QT_MOC_LITERAL(80, 1809, 38), // "on_CHANNEL_TRIGGER_checkBox_2..."
QT_MOC_LITERAL(81, 1848, 38), // "on_CHANNEL_TRIGGER_checkBox_2..."
QT_MOC_LITERAL(82, 1887, 38), // "on_CHANNEL_TRIGGER_checkBox_3..."
QT_MOC_LITERAL(83, 1926, 38), // "on_CHANNEL_TRIGGER_checkBox_3..."
QT_MOC_LITERAL(84, 1965, 38), // "on_CHANNEL_TRIGGER_checkBox_3..."
QT_MOC_LITERAL(85, 2004, 38), // "on_CHANNEL_TRIGGER_checkBox_3..."
QT_MOC_LITERAL(86, 2043, 38), // "on_CHANNEL_TRIGGER_checkBox_3..."
QT_MOC_LITERAL(87, 2082, 38), // "on_CHANNEL_TRIGGER_checkBox_4..."
QT_MOC_LITERAL(88, 2121, 38), // "on_CHANNEL_TRIGGER_checkBox_4..."
QT_MOC_LITERAL(89, 2160, 38), // "on_CHANNEL_TRIGGER_checkBox_4..."
QT_MOC_LITERAL(90, 2199, 38), // "on_CHANNEL_TRIGGER_checkBox_4..."
QT_MOC_LITERAL(91, 2238, 38), // "on_CHANNEL_TRIGGER_checkBox_4..."
QT_MOC_LITERAL(92, 2277, 38), // "on_CHANNEL_TRIGGER_checkBox_5..."
QT_MOC_LITERAL(93, 2316, 38), // "on_CHANNEL_TRIGGER_checkBox_5..."
QT_MOC_LITERAL(94, 2355, 38), // "on_CHANNEL_TRIGGER_checkBox_5..."
QT_MOC_LITERAL(95, 2394, 38), // "on_CHANNEL_TRIGGER_checkBox_5..."
QT_MOC_LITERAL(96, 2433, 38), // "on_CHANNEL_TRIGGER_checkBox_5..."
QT_MOC_LITERAL(97, 2472, 24), // "on_radioButton_9_clicked"
QT_MOC_LITERAL(98, 2497, 25), // "on_radioButton_10_clicked"
QT_MOC_LITERAL(99, 2523, 32), // "on_radioButton_root_tree_clicked"
QT_MOC_LITERAL(100, 2556, 23), // "on_spinBox_valueChanged"
QT_MOC_LITERAL(101, 2580, 7), // "Message"
QT_MOC_LITERAL(102, 2588, 22), // "InitializationComplete"
QT_MOC_LITERAL(103, 2611, 16), // "RedrawGraphsFull"
QT_MOC_LITERAL(104, 2628, 15), // "QVector<double>"
QT_MOC_LITERAL(105, 2644, 25), // "QVector<QVector<double> >"
QT_MOC_LITERAL(106, 2670, 13), // "TransferSpeed"
QT_MOC_LITERAL(107, 2684, 11), // "TriggerRate"
QT_MOC_LITERAL(108, 2696, 9), // "GraphData"
QT_MOC_LITERAL(109, 2706, 8), // "double**"
QT_MOC_LITERAL(110, 2715, 5), // "array"
QT_MOC_LITERAL(111, 2721, 4), // "rows"
QT_MOC_LITERAL(112, 2726, 4) // "cols"

    },
    "MainWindow\0Init\0\0QuitProgram\0"
    "InterruptTimeout\0Program_the_digitizer\0"
    "Restart\0Mask_the_channels\0Readout_loop\0"
    "StopReadout_loop\0ContinuousTrigger\0"
    "ContinuousWrite\0SetRecordLength\0value\0"
    "TestPattern\0EnableContinuousPlot\0"
    "DisableContinuousPlot\0MaskChannel\0"
    "SetTriggerValue\0MaskChannelAll\0"
    "CHANNEL_TRIGGER_signal\0CHANNEL_TRIGGER_all\0"
    "SetOutFileType\0on_pushButton_clicked\0"
    "on_radioButton_13_clicked\0"
    "on_radioButton_12_clicked\0on_checkBox_clicked\0"
    "on_spinBox_3_valueChanged\0arg1\0"
    "on_doubleSpinBox_valueChanged\0"
    "on_doubleSpinBox_2_valueChanged\0"
    "on_spinBox_4_valueChanged\0"
    "on_radioButton_15_clicked\0checked\0"
    "on_pushButton_2_clicked\0on_pushButton_3_clicked\0"
    "on_groupBox_3_clicked\0"
    "on_spinBox_4_editingFinished\0"
    "on_Test_Pattern_button_clicked\0"
    "on_pushButton_5_clicked\0on_pushButton_4_clicked\0"
    "on_checkBox_11_clicked\0on_checkBox_12_clicked\0"
    "on_checkBox_13_clicked\0on_checkBox_14_clicked\0"
    "on_checkBox_15_clicked\0on_checkBox_21_clicked\0"
    "on_checkBox_22_clicked\0on_checkBox_23_clicked\0"
    "on_verticalSlider_valueChanged\0"
    "on_spinBox_2_valueChanged\0"
    "on_pushButton_6_clicked\0"
    "on_pushButton_Reprogram_clicked\0"
    "on_checkBox_24_clicked\0on_checkBox_25_clicked\0"
    "on_checkBox_31_clicked\0on_checkBox_32_clicked\0"
    "on_checkBox_33_clicked\0on_checkBox_34_clicked\0"
    "on_checkBox_35_clicked\0on_checkBox_41_clicked\0"
    "on_checkBox_42_clicked\0on_checkBox_43_clicked\0"
    "on_checkBox_44_clicked\0on_checkBox_45_clicked\0"
    "on_checkBox_51_clicked\0on_checkBox_52_clicked\0"
    "on_checkBox_53_clicked\0on_checkBox_54_clicked\0"
    "on_checkBox_55_clicked\0on_pushButton_7_clicked\0"
    "on_pushButton_8_clicked\0"
    "on_CHANNEL_TRIGGER_checkBox_11_clicked\0"
    "on_CHANNEL_TRIGGER_checkBox_12_clicked\0"
    "on_CHANNEL_TRIGGER_checkBox_13_clicked\0"
    "on_CHANNEL_TRIGGER_checkBox_14_clicked\0"
    "on_CHANNEL_TRIGGER_checkBox_15_clicked\0"
    "on_CHANNEL_TRIGGER_checkBox_21_clicked\0"
    "on_CHANNEL_TRIGGER_checkBox_22_clicked\0"
    "on_CHANNEL_TRIGGER_checkBox_23_clicked\0"
    "on_CHANNEL_TRIGGER_checkBox_24_clicked\0"
    "on_CHANNEL_TRIGGER_checkBox_25_clicked\0"
    "on_CHANNEL_TRIGGER_checkBox_31_clicked\0"
    "on_CHANNEL_TRIGGER_checkBox_32_clicked\0"
    "on_CHANNEL_TRIGGER_checkBox_33_clicked\0"
    "on_CHANNEL_TRIGGER_checkBox_34_clicked\0"
    "on_CHANNEL_TRIGGER_checkBox_35_clicked\0"
    "on_CHANNEL_TRIGGER_checkBox_41_clicked\0"
    "on_CHANNEL_TRIGGER_checkBox_42_clicked\0"
    "on_CHANNEL_TRIGGER_checkBox_43_clicked\0"
    "on_CHANNEL_TRIGGER_checkBox_44_clicked\0"
    "on_CHANNEL_TRIGGER_checkBox_45_clicked\0"
    "on_CHANNEL_TRIGGER_checkBox_51_clicked\0"
    "on_CHANNEL_TRIGGER_checkBox_52_clicked\0"
    "on_CHANNEL_TRIGGER_checkBox_53_clicked\0"
    "on_CHANNEL_TRIGGER_checkBox_54_clicked\0"
    "on_CHANNEL_TRIGGER_checkBox_55_clicked\0"
    "on_radioButton_9_clicked\0"
    "on_radioButton_10_clicked\0"
    "on_radioButton_root_tree_clicked\0"
    "on_spinBox_valueChanged\0Message\0"
    "InitializationComplete\0RedrawGraphsFull\0"
    "QVector<double>\0QVector<QVector<double> >\0"
    "TransferSpeed\0TriggerRate\0GraphData\0"
    "double**\0array\0rows\0cols"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
     106,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      20,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  544,    2, 0x06 /* Public */,
       3,    0,  545,    2, 0x06 /* Public */,
       4,    0,  546,    2, 0x06 /* Public */,
       5,    0,  547,    2, 0x06 /* Public */,
       6,    0,  548,    2, 0x06 /* Public */,
       7,    0,  549,    2, 0x06 /* Public */,
       8,    0,  550,    2, 0x06 /* Public */,
       9,    0,  551,    2, 0x06 /* Public */,
      10,    0,  552,    2, 0x06 /* Public */,
      11,    0,  553,    2, 0x06 /* Public */,
      12,    1,  554,    2, 0x06 /* Public */,
      14,    0,  557,    2, 0x06 /* Public */,
      15,    0,  558,    2, 0x06 /* Public */,
      16,    0,  559,    2, 0x06 /* Public */,
      17,    2,  560,    2, 0x06 /* Public */,
      18,    2,  565,    2, 0x06 /* Public */,
      19,    1,  570,    2, 0x06 /* Public */,
      20,    2,  573,    2, 0x06 /* Public */,
      21,    1,  578,    2, 0x06 /* Public */,
      22,    1,  581,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      23,    0,  584,    2, 0x08 /* Private */,
      24,    0,  585,    2, 0x08 /* Private */,
      25,    0,  586,    2, 0x08 /* Private */,
      26,    0,  587,    2, 0x08 /* Private */,
      27,    1,  588,    2, 0x08 /* Private */,
      29,    1,  591,    2, 0x08 /* Private */,
      30,    1,  594,    2, 0x08 /* Private */,
      31,    1,  597,    2, 0x08 /* Private */,
      32,    1,  600,    2, 0x08 /* Private */,
      34,    0,  603,    2, 0x08 /* Private */,
      32,    0,  604,    2, 0x08 /* Private */,
      35,    0,  605,    2, 0x08 /* Private */,
      36,    0,  606,    2, 0x08 /* Private */,
      37,    0,  607,    2, 0x08 /* Private */,
      38,    0,  608,    2, 0x08 /* Private */,
      26,    1,  609,    2, 0x08 /* Private */,
      38,    1,  612,    2, 0x08 /* Private */,
      39,    0,  615,    2, 0x08 /* Private */,
      40,    0,  616,    2, 0x08 /* Private */,
      41,    1,  617,    2, 0x08 /* Private */,
      42,    1,  620,    2, 0x08 /* Private */,
      43,    1,  623,    2, 0x08 /* Private */,
      44,    1,  626,    2, 0x08 /* Private */,
      45,    1,  629,    2, 0x08 /* Private */,
      46,    1,  632,    2, 0x08 /* Private */,
      47,    1,  635,    2, 0x08 /* Private */,
      48,    1,  638,    2, 0x08 /* Private */,
      49,    1,  641,    2, 0x08 /* Private */,
      50,    1,  644,    2, 0x08 /* Private */,
      51,    0,  647,    2, 0x08 /* Private */,
      52,    0,  648,    2, 0x08 /* Private */,
      53,    1,  649,    2, 0x08 /* Private */,
      54,    1,  652,    2, 0x08 /* Private */,
      55,    1,  655,    2, 0x08 /* Private */,
      56,    1,  658,    2, 0x08 /* Private */,
      57,    1,  661,    2, 0x08 /* Private */,
      58,    1,  664,    2, 0x08 /* Private */,
      59,    1,  667,    2, 0x08 /* Private */,
      60,    1,  670,    2, 0x08 /* Private */,
      61,    1,  673,    2, 0x08 /* Private */,
      62,    1,  676,    2, 0x08 /* Private */,
      63,    1,  679,    2, 0x08 /* Private */,
      64,    1,  682,    2, 0x08 /* Private */,
      65,    1,  685,    2, 0x08 /* Private */,
      66,    1,  688,    2, 0x08 /* Private */,
      67,    1,  691,    2, 0x08 /* Private */,
      68,    1,  694,    2, 0x08 /* Private */,
      69,    1,  697,    2, 0x08 /* Private */,
      70,    0,  700,    2, 0x08 /* Private */,
      71,    0,  701,    2, 0x08 /* Private */,
      42,    0,  702,    2, 0x08 /* Private */,
      72,    1,  703,    2, 0x08 /* Private */,
      73,    1,  706,    2, 0x08 /* Private */,
      74,    1,  709,    2, 0x08 /* Private */,
      75,    1,  712,    2, 0x08 /* Private */,
      76,    1,  715,    2, 0x08 /* Private */,
      77,    1,  718,    2, 0x08 /* Private */,
      78,    1,  721,    2, 0x08 /* Private */,
      79,    1,  724,    2, 0x08 /* Private */,
      80,    1,  727,    2, 0x08 /* Private */,
      81,    1,  730,    2, 0x08 /* Private */,
      82,    1,  733,    2, 0x08 /* Private */,
      83,    1,  736,    2, 0x08 /* Private */,
      84,    1,  739,    2, 0x08 /* Private */,
      85,    1,  742,    2, 0x08 /* Private */,
      86,    1,  745,    2, 0x08 /* Private */,
      87,    1,  748,    2, 0x08 /* Private */,
      88,    1,  751,    2, 0x08 /* Private */,
      89,    1,  754,    2, 0x08 /* Private */,
      90,    1,  757,    2, 0x08 /* Private */,
      91,    1,  760,    2, 0x08 /* Private */,
      92,    1,  763,    2, 0x08 /* Private */,
      93,    1,  766,    2, 0x08 /* Private */,
      94,    1,  769,    2, 0x08 /* Private */,
      95,    1,  772,    2, 0x08 /* Private */,
      96,    1,  775,    2, 0x08 /* Private */,
      97,    1,  778,    2, 0x08 /* Private */,
      98,    1,  781,    2, 0x08 /* Private */,
      99,    1,  784,    2, 0x08 /* Private */,
     100,    1,  787,    2, 0x08 /* Private */,
     101,    1,  790,    2, 0x0a /* Public */,
     102,    0,  793,    2, 0x0a /* Public */,
     103,    2,  794,    2, 0x0a /* Public */,
     106,    1,  799,    2, 0x0a /* Public */,
     107,    1,  802,    2, 0x0a /* Public */,
     108,    3,  805,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   28,
    QMetaType::Void, QMetaType::Double,   28,
    QMetaType::Void, QMetaType::Double,   28,
    QMetaType::Void, QMetaType::Int,   28,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Int,   28,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Bool,   33,
    QMetaType::Void, QMetaType::Int,   28,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 104, 0x80000000 | 105,    2,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, 0x80000000 | 109, QMetaType::Int, QMetaType::Int,  110,  111,  112,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Init(); break;
        case 1: _t->QuitProgram(); break;
        case 2: _t->InterruptTimeout(); break;
        case 3: _t->Program_the_digitizer(); break;
        case 4: _t->Restart(); break;
        case 5: _t->Mask_the_channels(); break;
        case 6: _t->Readout_loop(); break;
        case 7: _t->StopReadout_loop(); break;
        case 8: _t->ContinuousTrigger(); break;
        case 9: _t->ContinuousWrite(); break;
        case 10: _t->SetRecordLength((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->TestPattern(); break;
        case 12: _t->EnableContinuousPlot(); break;
        case 13: _t->DisableContinuousPlot(); break;
        case 14: _t->MaskChannel((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 15: _t->SetTriggerValue((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 16: _t->MaskChannelAll((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: _t->CHANNEL_TRIGGER_signal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 18: _t->CHANNEL_TRIGGER_all((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 19: _t->SetOutFileType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->on_pushButton_clicked(); break;
        case 21: _t->on_radioButton_13_clicked(); break;
        case 22: _t->on_radioButton_12_clicked(); break;
        case 23: _t->on_checkBox_clicked(); break;
        case 24: _t->on_spinBox_3_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->on_doubleSpinBox_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 26: _t->on_doubleSpinBox_2_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 27: _t->on_spinBox_4_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: _t->on_radioButton_15_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 29: _t->on_pushButton_2_clicked(); break;
        case 30: _t->on_radioButton_15_clicked(); break;
        case 31: _t->on_pushButton_3_clicked(); break;
        case 32: _t->on_groupBox_3_clicked(); break;
        case 33: _t->on_spinBox_4_editingFinished(); break;
        case 34: _t->on_Test_Pattern_button_clicked(); break;
        case 35: _t->on_checkBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 36: _t->on_Test_Pattern_button_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 37: _t->on_pushButton_5_clicked(); break;
        case 38: _t->on_pushButton_4_clicked(); break;
        case 39: _t->on_checkBox_11_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 40: _t->on_checkBox_12_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 41: _t->on_checkBox_13_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 42: _t->on_checkBox_14_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 43: _t->on_checkBox_15_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 44: _t->on_checkBox_21_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 45: _t->on_checkBox_22_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 46: _t->on_checkBox_23_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 47: _t->on_verticalSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 48: _t->on_spinBox_2_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 49: _t->on_pushButton_6_clicked(); break;
        case 50: _t->on_pushButton_Reprogram_clicked(); break;
        case 51: _t->on_checkBox_24_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 52: _t->on_checkBox_25_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 53: _t->on_checkBox_31_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 54: _t->on_checkBox_32_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 55: _t->on_checkBox_33_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 56: _t->on_checkBox_34_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 57: _t->on_checkBox_35_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 58: _t->on_checkBox_41_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 59: _t->on_checkBox_42_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 60: _t->on_checkBox_43_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 61: _t->on_checkBox_44_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 62: _t->on_checkBox_45_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 63: _t->on_checkBox_51_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 64: _t->on_checkBox_52_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 65: _t->on_checkBox_53_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 66: _t->on_checkBox_54_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 67: _t->on_checkBox_55_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 68: _t->on_pushButton_7_clicked(); break;
        case 69: _t->on_pushButton_8_clicked(); break;
        case 70: _t->on_checkBox_12_clicked(); break;
        case 71: _t->on_CHANNEL_TRIGGER_checkBox_11_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 72: _t->on_CHANNEL_TRIGGER_checkBox_12_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 73: _t->on_CHANNEL_TRIGGER_checkBox_13_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 74: _t->on_CHANNEL_TRIGGER_checkBox_14_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 75: _t->on_CHANNEL_TRIGGER_checkBox_15_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 76: _t->on_CHANNEL_TRIGGER_checkBox_21_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 77: _t->on_CHANNEL_TRIGGER_checkBox_22_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 78: _t->on_CHANNEL_TRIGGER_checkBox_23_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 79: _t->on_CHANNEL_TRIGGER_checkBox_24_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 80: _t->on_CHANNEL_TRIGGER_checkBox_25_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 81: _t->on_CHANNEL_TRIGGER_checkBox_31_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 82: _t->on_CHANNEL_TRIGGER_checkBox_32_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 83: _t->on_CHANNEL_TRIGGER_checkBox_33_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 84: _t->on_CHANNEL_TRIGGER_checkBox_34_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 85: _t->on_CHANNEL_TRIGGER_checkBox_35_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 86: _t->on_CHANNEL_TRIGGER_checkBox_41_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 87: _t->on_CHANNEL_TRIGGER_checkBox_42_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 88: _t->on_CHANNEL_TRIGGER_checkBox_43_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 89: _t->on_CHANNEL_TRIGGER_checkBox_44_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 90: _t->on_CHANNEL_TRIGGER_checkBox_45_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 91: _t->on_CHANNEL_TRIGGER_checkBox_51_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 92: _t->on_CHANNEL_TRIGGER_checkBox_52_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 93: _t->on_CHANNEL_TRIGGER_checkBox_53_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 94: _t->on_CHANNEL_TRIGGER_checkBox_54_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 95: _t->on_CHANNEL_TRIGGER_checkBox_55_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 96: _t->on_radioButton_9_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 97: _t->on_radioButton_10_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 98: _t->on_radioButton_root_tree_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 99: _t->on_spinBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 100: _t->Message((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 101: _t->InitializationComplete(); break;
        case 102: _t->RedrawGraphsFull((*reinterpret_cast< QVector<double>(*)>(_a[1])),(*reinterpret_cast< QVector<QVector<double> >(*)>(_a[2]))); break;
        case 103: _t->TransferSpeed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 104: _t->TriggerRate((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 105: _t->GraphData((*reinterpret_cast< double**(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 102:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QVector<double> > >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<double> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::Init)) {
                *result = 0;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::QuitProgram)) {
                *result = 1;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::InterruptTimeout)) {
                *result = 2;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::Program_the_digitizer)) {
                *result = 3;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::Restart)) {
                *result = 4;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::Mask_the_channels)) {
                *result = 5;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::Readout_loop)) {
                *result = 6;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::StopReadout_loop)) {
                *result = 7;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::ContinuousTrigger)) {
                *result = 8;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::ContinuousWrite)) {
                *result = 9;
            }
        }
        {
            typedef void (MainWindow::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::SetRecordLength)) {
                *result = 10;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::TestPattern)) {
                *result = 11;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::EnableContinuousPlot)) {
                *result = 12;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::DisableContinuousPlot)) {
                *result = 13;
            }
        }
        {
            typedef void (MainWindow::*_t)(int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::MaskChannel)) {
                *result = 14;
            }
        }
        {
            typedef void (MainWindow::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::SetTriggerValue)) {
                *result = 15;
            }
        }
        {
            typedef void (MainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::MaskChannelAll)) {
                *result = 16;
            }
        }
        {
            typedef void (MainWindow::*_t)(int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::CHANNEL_TRIGGER_signal)) {
                *result = 17;
            }
        }
        {
            typedef void (MainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::CHANNEL_TRIGGER_all)) {
                *result = 18;
            }
        }
        {
            typedef void (MainWindow::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::SetOutFileType)) {
                *result = 19;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 106)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 106;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 106)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 106;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::Init()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void MainWindow::QuitProgram()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void MainWindow::InterruptTimeout()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void MainWindow::Program_the_digitizer()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void MainWindow::Restart()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void MainWindow::Mask_the_channels()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}

// SIGNAL 6
void MainWindow::Readout_loop()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}

// SIGNAL 7
void MainWindow::StopReadout_loop()
{
    QMetaObject::activate(this, &staticMetaObject, 7, Q_NULLPTR);
}

// SIGNAL 8
void MainWindow::ContinuousTrigger()
{
    QMetaObject::activate(this, &staticMetaObject, 8, Q_NULLPTR);
}

// SIGNAL 9
void MainWindow::ContinuousWrite()
{
    QMetaObject::activate(this, &staticMetaObject, 9, Q_NULLPTR);
}

// SIGNAL 10
void MainWindow::SetRecordLength(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void MainWindow::TestPattern()
{
    QMetaObject::activate(this, &staticMetaObject, 11, Q_NULLPTR);
}

// SIGNAL 12
void MainWindow::EnableContinuousPlot()
{
    QMetaObject::activate(this, &staticMetaObject, 12, Q_NULLPTR);
}

// SIGNAL 13
void MainWindow::DisableContinuousPlot()
{
    QMetaObject::activate(this, &staticMetaObject, 13, Q_NULLPTR);
}

// SIGNAL 14
void MainWindow::MaskChannel(int _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void MainWindow::SetTriggerValue(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void MainWindow::MaskChannelAll(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void MainWindow::CHANNEL_TRIGGER_signal(int _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void MainWindow::CHANNEL_TRIGGER_all(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void MainWindow::SetOutFileType(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}
QT_END_MOC_NAMESPACE
