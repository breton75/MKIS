#ifndef SQL_SELECT_DEFS
#define SQL_SELECT_DEFS

#include <QString>
#include "sql_fields_defs.h"

//using namespace sql_fields_defs;
//sql_fields_defs
//#define DEVICE_NAME "device_name"
//#define DEVICE_IP "ip"

namespace sql_select_defs
{
  
#define D_SELECT_DEV_DEVICES_LIST " SELECT " CR\
                                         "   id as id , " CR\
                                         "   device_name as device_name , " CR\
                                         "   device_model as device_model, " CR\
                                         "   device_class as device_class, " CR\
                                         "   device_brand as device_brand, " CR\
                                         "   ip  as ip, " CR\
                                         "   port  as port, " CR\
                                         "   driver_lib_path as driver_lib_path, " CRR\
                                         "   video_path  as video_path, " CR\
                                         "   pos_x  as pos_x, " CR\
                                         "   pos_y  as pos_y, " CR\
                                         "   zone_name  as zone_name, " CR\
                                         "   description  as description " CR\
                                         " FROM " CR\
                                         "   devices  ORDER BY id ASC"

  const QString D_DEV_DEVICES_LIST = "ID;Имя;Модель;Класс устройства;Производитель;IP;Порт;...;Координаты по X;Координаты по Y;Зона;Описание";

#define D_SELECT_FROM_DEVICES_WHERE_2 "SELECT " CRR\
                                        "  id as id, " CRR\
                                        "  device_name as device_name, " CRR\
                                        "  ip as ip, " CRR\
                                        "  port as port, " CRR\
                                        "  device_class as device_class, " CRR\
                                        "  device_brand as device_brand," CRR\
                                        "  device_model as device_model, " CRR\
                                        "  pos_x as pos_x, " CRR\
                                        "  pos_y as pos_y, " CRR\
                                        "  driver_lib_path as driver_lib_path, " CRR\  
                                        "  video_path as video_path, " CRR\
                                        "  zone_name as zone_name," CRR\
                                        "  description as description, " CRR\
                                        "  arch_config as arch_config " CR\
                                        "FROM " CRR\
                                        "  devices " CR\
                                        "WHERE %1 = %2"
  
 
  /******** device models ********/
 
  const QString D_SELECT_DEV_MODELS_LIST = " SELECT "
                                           "   id as id , "
                                           "   model_name as model_name, "
                                           "   model_brand as model_brand, "
                                           "   model_class as model_class, "
                                           "   model_lib_path as model_lib_path, "
                                           "   description as description "
                                           " FROM "
                                           "   models ORDER BY id ASC";
  
  const QString D_DEV_MODELS_COLUMN_LIST = "ID;Модель;Производитель;Класс устройства;Библиотека;Описание";
  
  
  /******** device brands *********/ 
  const QString D_SELECT_DEV_BRANDS_LIST = "SELECT " 
                                           "      id as id, "
                                           "      brand_name as brand_name, "
                                           "      description as description "
                                           "    FROM "
                                           "      brands ORDER BY id ASC";
  
  const QString D_DEV_BRANDS_COLUMN_LIST = "ID;Brand name;Description";
  
  
  /********* device classes ********/
  const QString D_SELECT_DEV_CLASSES_LIST = "SELECT " 
                                            "      id as id, "
                                            "      class_name as class_name, "
                                            "      description as description, "
                                            "      class_lib_path as class_lib_path "
                                            "    FROM "
                                            "      classes  ORDER BY id ASC";
  
  const QString D_DEV_CLASSES_COLUMN_LIST = "ID;Имя класса;Примечания;Библиотека";
  


  
/************ zones **********************/
#define D_SELECT_ZONES_LIST "SELECT " CRR\
                            "  id, zone_name, parent_zone_name, img_data, img_path," CRR\
                            "  points, scene_size, description " CR\
                            "FROM zones  ORDER BY id ASC"
  
#define D_ZONES_COLUMN_LIST "/Id/true;/Имя зоны/true;/Входит в.../true;/img_data/false;/Изображение/true;"\
                          "/points/false;/scene_size/false;/Описание/false"
  
#define D_SELECT_FROM_ZONES_WHERE "SELECT " CRR\
                                  "  id, zone_name, parent_zone_name, img_data, img_path," CRR\
                                  "  points, scene_size, description " CR\
                                  "FROM zones where %1=%2 "
  
  /**************** variables ***************/
#define D_SELECT_VARIABLES_LIST "SELECT " CRR\
                                "  id, var_name, device_name, min_value," CRR\
                                "  max_value, alarm_type, description, alarm_description " CR\
                                "FROM variables  ORDER BY id ASC"

/*************** scud keys ******************/
#define D_SELECT_SCUDS_LIST "SELECT scuds.id as id, " CRR\
                            "  scuds.key_value as key_value, " CRR\
                            "  scuds.employee_id as employee_id, " CRR\
                            "  scuds.device_name as device_name, " CRR\
                            "  scuds.zone_name as zone_name, " CRR\
                            "  employees.employee_name as employee_name, " CRR\
                            "  employees.employee_patronymic as employee_patronymic, " CRR\
                            "  employees.employee_surename as employee_surename," CRR\
                            "  employees.employee_position as employee_position" CR\
                            "from scuds left join employees on scuds.employee_id = employees.id"
  
#define D_SELECT_FROM_SCUDS_WHERE "SELECT scuds.id as id, " CRR\
                                  "  scuds.key_value as key_value, " CRR\
                                  "  scuds.employee_id as employee_id, " CRR\
                                  "  scuds.device_name as device_name, " CRR\
                                  "  scuds.zone_name as zone_name, " CRR\
                                  "  employees.employee_name as employee_name, " CRR\
                                  "  employees.employee_patronymic as employee_patronymic, " CRR\
                                  "  employees.employee_surename as employee_surename," CRR\
                                  "  employees.employee_position as employee_position" CR\
                                  "from scuds left join employees on scuds.employee_id = employees.id" CR\
                                  "where %1=%2"  
  
  
  /**************** employers ***************/
#define D_SELECT_FROM_EMPLOYEES_WHERE "SELECT " CRR\
                                      "  employees.id as id, " CRR\
                                      "  employees.employee_name as employee_name," CRR\
                                      "  employees.employee_patronymic as employee_patronymic, " CRR\
                                      "  employees.employee_surename as employee_surename," CRR\
                                      "  employees.birth_date as birth_date," CRR\
                                      "  employees.employee_position as employee_position," CRR\
                                      "  employees.key_id as key_id," CRR\
                                      "  scuds.key_value as key_value," CRR\
                                      "  employees.description as description" CRR\
                                      "FROM employees LEFT JOIN scuds ON employees.key_id = scuds.id "CR\
                                      "WHERE employees.id = %1" 

#define D_SELECT_EMPLOYEES_LIST "SELECT " CRR\
                                "  employees.id as id, " CRR\
                                "  employees.employee_name as employee_name," CRR\
                                "  employees.employee_patronymic as employee_patronymic, " CRR\
                                "  employees.employee_surename as employee_surename," CRR\
                                "  employees.employee_position as employee_position," CRR\
                                "  employees.birth_date as birth_date," CRR\
                                "  employees.key_id as key_id," CRR\
                                "  scuds.key_value as key_value," CRR\
                                "  employees.description as description" CRR\
                                "FROM employees LEFT JOIN scuds ON employees.key_id = scuds.id ORDER BY employees.id ASC"

#define D_EMPLOYEES_COLUMN_LIST "/ID/true;/Имя/true;/Отчество/true;/Фамилия/true;/Должность/true;"\
                                "/Дата рождения/true;/key_id/false;/Ключ/true;/Примечания/true"


  
  /********** АРХИВЫ **************/
  
  /********** видео **************/
#define D_SELECT_ARHC_VIDEO_LIST "select " CRR\
																 "  arch_video.id as id, " CRR\
	  														 "	devices.device_name as device_name, " CRR\
	  														 "  devices.device_model as device_model, " CRR\
	  														 "  devices.ip as ip," CRR\
																 "	arch_video.record_begin as record_begin, " CRR\
																 "	arch_video.record_end as record_end, " CRR\
																 "	arch_video.device_id as device_id, " CRR\
																 "	arch_video.file_name as file_name " CR\
																 "from arch_video " CR\
															   "left join devices on arch_video.device_id = devices.id order by arch_video.id ASC"

#define D_ARCHVIDEO_COLUMN_LIST "/ID/true;/Устройство/true;/Модель/true;/IP/true;"\
																 "/Начало записи/true;/Конец записи/true;/device_id/false;/file_name/false"
	
#define D_SELECT_FROM_ARHC_VIDEO_WHERE "select " CRR\
																 "  arch_video.id as id, " CRR\
	  														 "	devices.device_name as device_name, " CRR\
	  														 "  devices.device_model as device_model, " CRR\
	  														 "  devices.ip as ip," CRR\
																 "	arch_video.record_begin as record_begin, " CRR\
																 "	arch_video.record_end as record_end, " CRR\
																 "	arch_video.device_id as device_id, " CRR\
																 "	arch_video.file_name as file_name " CR\
																 "from arch_video " CR\
															   "left join devices on arch_video.device_id = devices.id " CR\
																 "where %1=%2"

/************* СКУД ***************/
#define D_SELECT_ARHC_SCUD_LIST "select " CRR\
                                 "  scud_history.date_time as date_time, " CRR\
                                 "  scud_history.key_value as key_value, " CRR\                                 
                                 "  scud_history.sensor_number as sensor_number, " CRR\
                                 "  scud_history.ip as ip, " CRR\
                                 "  scuds.zone_name as zone_name, " CRR\
                                 "  employees.employee_name as employee_name, " CRR\
                                 "  employees.employee_patronymic as employee_patronymic, " CRR\
                                 "  employees.employee_surename as employee_surename, " CRR\
                                 "  employees.employee_position as employee_position " CR\
                                 "from scud_history " CRR\
                                 "left join scuds on scud_history.key_value = scuds.key_value " CR\
                                 "left join employees on scuds.employee_id = employees.id " CR\

#define D_ARCHSCUD_COLUMN_LIST "/Дата\Время/true;/Ключ/true;/№ считывателя/true;/IP/true;"\
																 "/Зона/true;/employee_name/false;/employee_patronymic/false;"\
																 "/Сотрудник/true;/Должность/true"	




}

namespace sql_insert_defs {
  
  /* *********** DEVICES *********** */
  
  const QString D_INSERT_INTO_DEVICES      = "insert into devices (device_name, device_model, device_class, device_brand, ip, port, driver_lib_path, pos_x, pos_y, zone_name, description) " \
                                       "values('%1', '%2', '%3', '%4', '%5', %6, '%7', %8, %9, '%10', '%11')";
  
  const QString D_UPDATE_DEV_DEVICES      = "update devices set device_name='%1', device_model='%2', device_class='%3', device_brand='%4', ip='%5', port=%6, driver_lib_path='%7', pos_x=%8, pos_y=%9, zone_name='%10', " \
                                         "description='%11' where id=%12";
  
#define D_UPDATE_DEVICE_POSITION "update devices set pos_x=%1, pos_y=%2 where device_name='%3' and zone_name='%4'"

  const QString D_DELETE_FROM_DEVICES= "delete from devices where id=%1";
  
#define INSERT_INTO_ARCH_DEVICE "insert into " TBL_ARCH " (" F_ARCH_ARCHIVER_ID ", "\
                                    F_ARCH_DATA_TYPE ", "\
                                    F_ARCH_DATA_ID ")" CR\
                                    " values (%1, %2, %3)"
  
#define DELETE_FROM_ARCH_WHERE_IN "delete from " TBL_ARCH " where " F_ARCH_DATA_TYPE "=%1 and " F_ARCH_DATA_ID " in (%2)" 
  
  
  /* ********* DEV MODELS ************ */
  const QString D_INSERT_INTO_DEV_MODELS = "insert into models (model_name, model_brand, model_class, model_lib_path,  description) " \
                                         "values('%1', '%2', '%3', '%4', '%5')";
  
  
  const QString D_UPDATE_DEV_MODELS      = "update models set model_name='%1', model_class='%2', model_brand='%3', model_lib_path='%4', " \
                                         "description='%5' where id=%6";
  
  const QString DELETE_FROM_DEV_MODELS = "delete from dev_models where id=%1";
  
  
  
  
  /* *********** DEV BRANDS ************** */
  const QString D_INSERT_INTO_DEV_BRANDS = "insert into brands (brand_name, description) " \
                                         "values('%1', '%2')";
  
  const QString D_UPDATE_DEV_BRANDS      = "update brands set brand_name='%1', description='%2' where id=%3" ;
  
  const QString D_DELETE_FROM_DEV_BRANDS = "delete from dev_brands where id=%1";
  
  
  
  /* *********** DEV CLASSES ************** */
  const QString D_INSERT_INTO_DEV_CLASSES = "insert into classes (class_name, description,class_lib_path) " \
                                         "values('%1', '%2', '%3')";
  
  const QString D_UPDATE_DEV_CLASSES      = "update classes set class_name='%1'," \
                                          "description='%2' ,class_lib_path='%3' where id=%4";
  
  const QString DELETE_FROM_DEV_CLASSES = "delete from dev_classes where id=%1";
  
  
  /************ zones **********************/
#define D_INSERT_INTO_ZONES "insert into zones " CRR\
                            " (zone_name, parent_zone_name, img_path, description) " CR\
                            " values('%1', '%2', '%3', '%4') "
  
#define D_UPDATE_ZONES       "update zones set zone_name='%1', parent_zone_name='%2', img_path='%3', description='%4'  where id=%5" 
  
#define D_UPDATE_ZONE_POINTS "update zones set points='%1', scene_size=%2 where zone_name='%3'"

/*********** scud keys ******************/
#define D_INSERT_INTO_SCUDS "insert into scuds (key_value, employee_id, device_name, zone_name) " CR\
                            "values(%1, %2, '%3', '%4')"

#define D_UPDATE_SCUDS "update scuds set key_value=%1, employee_id=%2, " CR\
                       "device_name='%3', zone_name='%4' where key_value='%5'"


  /*********** employees ******************/
#define D_INSERT_INTO_EMPLOYEES "insert into employees (employee_name," \
                                "  employee_patronymic, "\
                                "  employee_surename, "\
                                "  employee_position, "\
                                "  birth_date, "\
                                "  key_id, "\
                                "  description) " CR\
                                "values('%1', '%2', '%3', '%4', '%5', %6, '%7')"

#define D_UPDATE_EMPLOYEES "update employees set "\
                           "  employee_name='%1', " \
                           "  employee_patronymic='%2', "\
                           "  employee_surename='%3', "\
                           "  employee_position='%4', "\
                           "  birth_date='%5', "\
                           "  key_id=%6, "\
                           "  description='%7' "\
                           "where id='%8'"


}

#endif // SQL_DEFS

