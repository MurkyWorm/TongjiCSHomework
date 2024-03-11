-- MySQL dump 10.13  Distrib 8.0.32, for Win64 (x86_64)
--
-- Host: localhost    Database: storys
-- ------------------------------------------------------
-- Server version	8.0.32

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `auth_group`
--

DROP TABLE IF EXISTS `auth_group`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `auth_group` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(150) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `auth_group`
--

LOCK TABLES `auth_group` WRITE;
/*!40000 ALTER TABLE `auth_group` DISABLE KEYS */;
/*!40000 ALTER TABLE `auth_group` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `auth_group_permissions`
--

DROP TABLE IF EXISTS `auth_group_permissions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `auth_group_permissions` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `group_id` int NOT NULL,
  `permission_id` int NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `auth_group_permissions_group_id_permission_id_0cd325b0_uniq` (`group_id`,`permission_id`),
  KEY `auth_group_permissio_permission_id_84c5c92e_fk_auth_perm` (`permission_id`),
  CONSTRAINT `auth_group_permissio_permission_id_84c5c92e_fk_auth_perm` FOREIGN KEY (`permission_id`) REFERENCES `auth_permission` (`id`),
  CONSTRAINT `auth_group_permissions_group_id_b120cbf9_fk_auth_group_id` FOREIGN KEY (`group_id`) REFERENCES `auth_group` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `auth_group_permissions`
--

LOCK TABLES `auth_group_permissions` WRITE;
/*!40000 ALTER TABLE `auth_group_permissions` DISABLE KEYS */;
/*!40000 ALTER TABLE `auth_group_permissions` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `auth_permission`
--

DROP TABLE IF EXISTS `auth_permission`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `auth_permission` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `content_type_id` int NOT NULL,
  `codename` varchar(100) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `auth_permission_content_type_id_codename_01ab375a_uniq` (`content_type_id`,`codename`),
  CONSTRAINT `auth_permission_content_type_id_2f476e4b_fk_django_co` FOREIGN KEY (`content_type_id`) REFERENCES `django_content_type` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=81 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `auth_permission`
--

LOCK TABLES `auth_permission` WRITE;
/*!40000 ALTER TABLE `auth_permission` DISABLE KEYS */;
INSERT INTO `auth_permission` VALUES (1,'Can add log entry',1,'add_logentry'),(2,'Can change log entry',1,'change_logentry'),(3,'Can delete log entry',1,'delete_logentry'),(4,'Can view log entry',1,'view_logentry'),(5,'Can add permission',2,'add_permission'),(6,'Can change permission',2,'change_permission'),(7,'Can delete permission',2,'delete_permission'),(8,'Can view permission',2,'view_permission'),(9,'Can add group',3,'add_group'),(10,'Can change group',3,'change_group'),(11,'Can delete group',3,'delete_group'),(12,'Can view group',3,'view_group'),(13,'Can add user',4,'add_user'),(14,'Can change user',4,'change_user'),(15,'Can delete user',4,'delete_user'),(16,'Can view user',4,'view_user'),(17,'Can add content type',5,'add_contenttype'),(18,'Can change content type',5,'change_contenttype'),(19,'Can delete content type',5,'delete_contenttype'),(20,'Can view content type',5,'view_contenttype'),(21,'Can add session',6,'add_session'),(22,'Can change session',6,'change_session'),(23,'Can delete session',6,'delete_session'),(24,'Can view session',6,'view_session'),(25,'Can add users',7,'add_users'),(26,'Can change users',7,'change_users'),(27,'Can delete users',7,'delete_users'),(28,'Can view users',7,'view_users'),(29,'Can add users',8,'add_users'),(30,'Can change users',8,'change_users'),(31,'Can delete users',8,'delete_users'),(32,'Can view users',8,'view_users'),(33,'Can add user_info',9,'add_user_info'),(34,'Can change user_info',9,'change_user_info'),(35,'Can delete user_info',9,'delete_user_info'),(36,'Can view user_info',9,'view_user_info'),(37,'Can add coll',10,'add_coll'),(38,'Can change coll',10,'change_coll'),(39,'Can delete coll',10,'delete_coll'),(40,'Can view coll',10,'view_coll'),(41,'Can add comment',11,'add_comment'),(42,'Can change comment',11,'change_comment'),(43,'Can delete comment',11,'delete_comment'),(44,'Can view comment',11,'view_comment'),(45,'Can add concen',12,'add_concen'),(46,'Can change concen',12,'change_concen'),(47,'Can delete concen',12,'delete_concen'),(48,'Can view concen',12,'view_concen'),(49,'Can add creation',13,'add_creation'),(50,'Can change creation',13,'change_creation'),(51,'Can delete creation',13,'delete_creation'),(52,'Can view creation',13,'view_creation'),(53,'Can add refer',14,'add_refer'),(54,'Can change refer',14,'change_refer'),(55,'Can delete refer',14,'delete_refer'),(56,'Can view refer',14,'view_refer'),(57,'Can add like',15,'add_like'),(58,'Can change like',15,'change_like'),(59,'Can delete like',15,'delete_like'),(60,'Can view like',15,'view_like'),(61,'Can add user_inter',16,'add_user_inter'),(62,'Can change user_inter',16,'change_user_inter'),(63,'Can delete user_inter',16,'delete_user_inter'),(64,'Can view user_inter',16,'view_user_inter'),(65,'Can add dislike',17,'add_dislike'),(66,'Can change dislike',17,'change_dislike'),(67,'Can delete dislike',17,'delete_dislike'),(68,'Can view dislike',17,'view_dislike'),(69,'Can add cdislike',18,'add_cdislike'),(70,'Can change cdislike',18,'change_cdislike'),(71,'Can delete cdislike',18,'delete_cdislike'),(72,'Can view cdislike',18,'view_cdislike'),(73,'Can add clike',19,'add_clike'),(74,'Can change clike',19,'change_clike'),(75,'Can delete clike',19,'delete_clike'),(76,'Can view clike',19,'view_clike'),(77,'Can add message',20,'add_message'),(78,'Can change message',20,'change_message'),(79,'Can delete message',20,'delete_message'),(80,'Can view message',20,'view_message');
/*!40000 ALTER TABLE `auth_permission` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `auth_user`
--

DROP TABLE IF EXISTS `auth_user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `auth_user` (
  `id` int NOT NULL AUTO_INCREMENT,
  `password` varchar(128) NOT NULL,
  `last_login` datetime(6) DEFAULT NULL,
  `is_superuser` tinyint(1) NOT NULL,
  `username` varchar(150) NOT NULL,
  `first_name` varchar(150) NOT NULL,
  `last_name` varchar(150) NOT NULL,
  `email` varchar(254) NOT NULL,
  `is_staff` tinyint(1) NOT NULL,
  `is_active` tinyint(1) NOT NULL,
  `date_joined` datetime(6) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `auth_user`
--

LOCK TABLES `auth_user` WRITE;
/*!40000 ALTER TABLE `auth_user` DISABLE KEYS */;
INSERT INTO `auth_user` VALUES (1,'pbkdf2_sha256$600000$tLuPGDhhy3FTCYxhFCYVJr$cpzEkvgMpAGitZxYpkpDQB0e/3uZlA0rwoL7WdvRJec=','2023-06-24 02:42:02.565747',1,'admin','','','zcr2152809@gmail.com',1,1,'2023-06-22 02:37:48.715654');
/*!40000 ALTER TABLE `auth_user` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `auth_user_groups`
--

DROP TABLE IF EXISTS `auth_user_groups`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `auth_user_groups` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `user_id` int NOT NULL,
  `group_id` int NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `auth_user_groups_user_id_group_id_94350c0c_uniq` (`user_id`,`group_id`),
  KEY `auth_user_groups_group_id_97559544_fk_auth_group_id` (`group_id`),
  CONSTRAINT `auth_user_groups_group_id_97559544_fk_auth_group_id` FOREIGN KEY (`group_id`) REFERENCES `auth_group` (`id`),
  CONSTRAINT `auth_user_groups_user_id_6a12ed8b_fk_auth_user_id` FOREIGN KEY (`user_id`) REFERENCES `auth_user` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `auth_user_groups`
--

LOCK TABLES `auth_user_groups` WRITE;
/*!40000 ALTER TABLE `auth_user_groups` DISABLE KEYS */;
/*!40000 ALTER TABLE `auth_user_groups` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `auth_user_user_permissions`
--

DROP TABLE IF EXISTS `auth_user_user_permissions`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `auth_user_user_permissions` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `user_id` int NOT NULL,
  `permission_id` int NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `auth_user_user_permissions_user_id_permission_id_14a6b632_uniq` (`user_id`,`permission_id`),
  KEY `auth_user_user_permi_permission_id_1fbb5f2c_fk_auth_perm` (`permission_id`),
  CONSTRAINT `auth_user_user_permi_permission_id_1fbb5f2c_fk_auth_perm` FOREIGN KEY (`permission_id`) REFERENCES `auth_permission` (`id`),
  CONSTRAINT `auth_user_user_permissions_user_id_a95ead1b_fk_auth_user_id` FOREIGN KEY (`user_id`) REFERENCES `auth_user` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `auth_user_user_permissions`
--

LOCK TABLES `auth_user_user_permissions` WRITE;
/*!40000 ALTER TABLE `auth_user_user_permissions` DISABLE KEYS */;
/*!40000 ALTER TABLE `auth_user_user_permissions` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `django_admin_log`
--

DROP TABLE IF EXISTS `django_admin_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `django_admin_log` (
  `id` int NOT NULL AUTO_INCREMENT,
  `action_time` datetime(6) NOT NULL,
  `object_id` longtext,
  `object_repr` varchar(200) NOT NULL,
  `action_flag` smallint unsigned NOT NULL,
  `change_message` longtext NOT NULL,
  `content_type_id` int DEFAULT NULL,
  `user_id` int NOT NULL,
  PRIMARY KEY (`id`),
  KEY `django_admin_log_content_type_id_c4bce8eb_fk_django_co` (`content_type_id`),
  KEY `django_admin_log_user_id_c564eba6_fk_auth_user_id` (`user_id`),
  CONSTRAINT `django_admin_log_content_type_id_c4bce8eb_fk_django_co` FOREIGN KEY (`content_type_id`) REFERENCES `django_content_type` (`id`),
  CONSTRAINT `django_admin_log_user_id_c564eba6_fk_auth_user_id` FOREIGN KEY (`user_id`) REFERENCES `auth_user` (`id`),
  CONSTRAINT `django_admin_log_chk_1` CHECK ((`action_flag` >= 0))
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `django_admin_log`
--

LOCK TABLES `django_admin_log` WRITE;
/*!40000 ALTER TABLE `django_admin_log` DISABLE KEYS */;
INSERT INTO `django_admin_log` VALUES (1,'2023-06-22 02:57:35.971099','5','Users object (5)',2,'[{\"changed\": {\"fields\": [\"Admin right\"]}}]',8,1),(2,'2023-06-22 08:02:50.486341','6','Users object (6)',2,'[{\"changed\": {\"fields\": [\"Admin right\"]}}]',8,1),(3,'2023-06-23 14:53:03.634104','10','Users object (10)',2,'[{\"changed\": {\"fields\": [\"Admin right\"]}}]',8,1),(4,'2023-06-24 00:36:50.627176','65','Creation object (65)',3,'',13,1);
/*!40000 ALTER TABLE `django_admin_log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `django_content_type`
--

DROP TABLE IF EXISTS `django_content_type`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `django_content_type` (
  `id` int NOT NULL AUTO_INCREMENT,
  `app_label` varchar(100) NOT NULL,
  `model` varchar(100) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `django_content_type_app_label_model_76bd3d3b_uniq` (`app_label`,`model`)
) ENGINE=InnoDB AUTO_INCREMENT=21 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `django_content_type`
--

LOCK TABLES `django_content_type` WRITE;
/*!40000 ALTER TABLE `django_content_type` DISABLE KEYS */;
INSERT INTO `django_content_type` VALUES (1,'admin','logentry'),(3,'auth','group'),(2,'auth','permission'),(4,'auth','user'),(5,'contenttypes','contenttype'),(9,'HOME','user_info'),(18,'INTERACT','cdislike'),(19,'INTERACT','clike'),(10,'INTERACT','coll'),(11,'INTERACT','comment'),(12,'INTERACT','concen'),(13,'INTERACT','creation'),(17,'INTERACT','dislike'),(15,'INTERACT','like'),(20,'INTERACT','message'),(14,'INTERACT','refer'),(16,'INTERACT','user_inter'),(8,'REG_LOG','users'),(7,'reglog','users'),(6,'sessions','session');
/*!40000 ALTER TABLE `django_content_type` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `django_migrations`
--

DROP TABLE IF EXISTS `django_migrations`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `django_migrations` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `app` varchar(255) NOT NULL,
  `name` varchar(255) NOT NULL,
  `applied` datetime(6) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=33 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `django_migrations`
--

LOCK TABLES `django_migrations` WRITE;
/*!40000 ALTER TABLE `django_migrations` DISABLE KEYS */;
INSERT INTO `django_migrations` VALUES (1,'contenttypes','0001_initial','2023-06-13 01:30:01.886085'),(2,'auth','0001_initial','2023-06-13 01:30:02.075740'),(3,'admin','0001_initial','2023-06-13 01:30:02.127743'),(4,'admin','0002_logentry_remove_auto_add','2023-06-13 01:30:02.132731'),(5,'admin','0003_logentry_add_action_flag_choices','2023-06-13 01:30:02.137302'),(6,'contenttypes','0002_remove_content_type_name','2023-06-13 01:30:02.169673'),(7,'auth','0002_alter_permission_name_max_length','2023-06-13 01:30:02.192626'),(8,'auth','0003_alter_user_email_max_length','2023-06-13 01:30:02.206169'),(9,'auth','0004_alter_user_username_opts','2023-06-13 01:30:02.210235'),(10,'auth','0005_alter_user_last_login_null','2023-06-13 01:30:02.232080'),(11,'auth','0006_require_contenttypes_0002','2023-06-13 01:30:02.234480'),(12,'auth','0007_alter_validators_add_error_messages','2023-06-13 01:30:02.239280'),(13,'auth','0008_alter_user_username_max_length','2023-06-13 01:30:02.262809'),(14,'auth','0009_alter_user_last_name_max_length','2023-06-13 01:30:02.285576'),(15,'auth','0010_alter_group_name_max_length','2023-06-13 01:30:02.298642'),(16,'auth','0011_update_proxy_permissions','2023-06-13 01:30:02.303320'),(17,'auth','0012_alter_user_first_name_max_length','2023-06-13 01:30:02.326163'),(18,'sessions','0001_initial','2023-06-13 01:30:02.341691'),(19,'reglog','0001_initial','2023-06-13 01:30:52.521936'),(20,'REG_LOG','0001_initial','2023-06-13 07:20:57.114869'),(21,'HOME','0001_initial','2023-06-18 08:55:01.139062'),(22,'HOME','0002_user_info_user_reply','2023-06-18 09:39:52.802734'),(23,'INTERACT','0001_initial','2023-06-19 01:17:55.989378'),(24,'INTERACT','0002_alter_creation_is_punish','2023-06-19 01:18:49.665255'),(25,'INTERACT','0003_delete_user_inter','2023-06-19 01:31:34.822040'),(26,'INTERACT','0004_creation_creation_id','2023-06-19 09:37:07.404377'),(27,'INTERACT','0005_creation_title','2023-06-19 10:04:34.342169'),(28,'INTERACT','0006_creation_comment_creation_dislike_creation_like_and_more','2023-06-19 12:41:24.778669'),(29,'INTERACT','0007_comment_type_like_type','2023-06-19 15:29:43.376201'),(30,'INTERACT','0008_dislike','2023-06-19 15:30:43.680981'),(31,'INTERACT','0009_cdislike_clike_comment_dislike_comment_like','2023-06-20 09:32:45.278446'),(32,'INTERACT','0010_message','2023-06-21 14:08:46.197327');
/*!40000 ALTER TABLE `django_migrations` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `django_session`
--

DROP TABLE IF EXISTS `django_session`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `django_session` (
  `session_key` varchar(40) NOT NULL,
  `session_data` longtext NOT NULL,
  `expire_date` datetime(6) NOT NULL,
  PRIMARY KEY (`session_key`),
  KEY `django_session_expire_date_a5c62663` (`expire_date`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `django_session`
--

LOCK TABLES `django_session` WRITE;
/*!40000 ALTER TABLE `django_session` DISABLE KEYS */;
INSERT INTO `django_session` VALUES ('0wcm01b6xmjre05hg9wqr8x3wqvzgk2w','.eJxVjDsOwjAQBe_iGln-O6Gk5wzWrr2LA8iR4qRC3B0ipYD2zcx7iQTbWtPWaUlTEWehxel3Q8gPajsod2i3Wea5rcuEclfkQbu8zoWel8P9O6jQ67dWgzfMlo0rSvEYcfBRoVHoQWOOjmwmCEEz5jBqYorGBqfRx2jBuyDeH94sN5w:1qCEkN:LgUIROPnW6_q3RXvRT2bc2yNjw7tEaTwYtwClvAqvZk','2023-07-06 07:28:51.899336'),('2z2knt4dlfwsqnd8kix0mzsdq6p6acw7','.eJxVjDsOwjAQBe_iGln-O6Gk5wzWrr2LA8iR4qRC3B0ipYD2zcx7iQTbWtPWaUlTEWehxel3Q8gPajsod2i3Wea5rcuEclfkQbu8zoWel8P9O6jQ67dWgzfMlo0rSvEYcfBRoVHoQWOOjmwmCEEz5jBqYorGBqfRx2jBuyDeH94sN5w:1qCADw:rfx44ap_NO0V-W2UnfrizBbhYYM0JUj2dLLqoGMH2Yc','2023-07-06 02:39:04.432102'),('5t97t4pceqaau1iwoqffzig2mpk3ew1f','.eJxVjDsOwjAQBe_iGln-O6Gk5wzWrr2LA8iR4qRC3B0ipYD2zcx7iQTbWtPWaUlTEWehxel3Q8gPajsod2i3Wea5rcuEclfkQbu8zoWel8P9O6jQ67dWgzfMlo0rSvEYcfBRoVHoQWOOjmwmCEEz5jBqYorGBqfRx2jBuyDeH94sN5w:1qCsyD:T7TdZyEx1z0kAMLeXnJSl4416uUn78QU5AqR5PhRvfo','2023-07-08 02:25:49.981588'),('g27938niwy66fn82hmgrpq40d8tloew2','.eJxVjDsOwjAQBe_iGln-O6Gk5wzWrr2LA8iR4qRC3B0ipYD2zcx7iQTbWtPWaUlTEWehxel3Q8gPajsod2i3Wea5rcuEclfkQbu8zoWel8P9O6jQ67dWgzfMlo0rSvEYcfBRoVHoQWOOjmwmCEEz5jBqYorGBqfRx2jBuyDeH94sN5w:1qCARD:5S1tZ5n0k7ydjy-0KZb4aAskVV5_ebEtnfdHvpfFB54','2023-07-06 02:52:47.941813'),('h3hd7j5il0d4m5bizbk29s47gm9gw6bv','.eJxVjDsOwjAQBe_iGln-O6Gk5wzWrr2LA8iR4qRC3B0ipYD2zcx7iQTbWtPWaUlTEWehxel3Q8gPajsod2i3Wea5rcuEclfkQbu8zoWel8P9O6jQ67dWgzfMlo0rSvEYcfBRoVHoQWOOjmwmCEEz5jBqYorGBqfRx2jBuyDeH94sN5w:1qCtDu:KqZAMH5CBeQkuAc-sHq61ehmXwYJ_4dRXa7fy_NvkHU','2023-07-08 02:42:02.567527'),('ns8c0bx71x1sn3401wlji2b8fjg0k1t7','.eJxVjDsOwjAQBe_iGln-O6Gk5wzWrr2LA8iR4qRC3B0ipYD2zcx7iQTbWtPWaUlTEWehxel3Q8gPajsod2i3Wea5rcuEclfkQbu8zoWel8P9O6jQ67dWgzfMlo0rSvEYcfBRoVHoQWOOjmwmCEEz5jBqYorGBqfRx2jBuyDeH94sN5w:1qCFGs:OEOng4kJfV8VAingXy91zp7gfYf0z-yCW-NylTr9QsM','2023-07-06 08:02:26.438228');
/*!40000 ALTER TABLE `django_session` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `home_user_info`
--

DROP TABLE IF EXISTS `home_user_info`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `home_user_info` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `user_name` varchar(20) NOT NULL,
  `user_pp` varchar(25) NOT NULL,
  `user_ideas` int NOT NULL,
  `user_echo` int NOT NULL,
  `user_fan` int NOT NULL,
  `user_like` int NOT NULL,
  `user_concen` int NOT NULL,
  `user_coll` int NOT NULL,
  `user_generate` int NOT NULL,
  `user_gender` varchar(20) NOT NULL,
  `user_age` int NOT NULL,
  `user_nature` varchar(20) NOT NULL,
  `user_prefer` varchar(20) NOT NULL,
  `user_reply` int NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `home_user_info`
--

LOCK TABLES `home_user_info` WRITE;
/*!40000 ALTER TABLE `home_user_info` DISABLE KEYS */;
INSERT INTO `home_user_info` VALUES (4,'jing','pp_jing',1,0,1,1,1,1,0,'男',20,'好','未设置',3),(5,'1','initial',3,0,3,7,0,1,0,'未设置',0,'未设置','未设置',4),(6,'Lu','initial',3,0,2,4,0,0,0,'未设置',0,'未设置','未设置',1),(7,'没有问题','initial',2,0,0,0,0,0,0,'未设置',0,'未设置','未设置',0),(8,'星期五','pp_星期五',0,0,0,0,1,2,0,'未设置',0,'未设置','未设置',0),(9,'星期六','initial',1,0,0,1,1,2,0,'未设置',0,'未设置','未设置',0);
/*!40000 ALTER TABLE `home_user_info` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `interact_cdislike`
--

DROP TABLE IF EXISTS `interact_cdislike`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `interact_cdislike` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `user_name` varchar(20) NOT NULL,
  `target` varchar(20) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=15 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `interact_cdislike`
--

LOCK TABLES `interact_cdislike` WRITE;
/*!40000 ALTER TABLE `interact_cdislike` DISABLE KEYS */;
INSERT INTO `interact_cdislike` VALUES (12,'jing','24'),(14,'jing','25');
/*!40000 ALTER TABLE `interact_cdislike` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `interact_clike`
--

DROP TABLE IF EXISTS `interact_clike`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `interact_clike` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `user_name` varchar(20) NOT NULL,
  `target` varchar(20) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=21 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `interact_clike`
--

LOCK TABLES `interact_clike` WRITE;
/*!40000 ALTER TABLE `interact_clike` DISABLE KEYS */;
/*!40000 ALTER TABLE `interact_clike` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `interact_coll`
--

DROP TABLE IF EXISTS `interact_coll`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `interact_coll` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `user_name` varchar(20) NOT NULL,
  `creation_name` varchar(100) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=44 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `interact_coll`
--

LOCK TABLES `interact_coll` WRITE;
/*!40000 ALTER TABLE `interact_coll` DISABLE KEYS */;
INSERT INTO `interact_coll` VALUES (37,'1','61'),(39,'星期五','63'),(40,'星期五','64'),(41,'jing','64'),(42,'星期六','67'),(43,'星期六','64');
/*!40000 ALTER TABLE `interact_coll` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `interact_comment`
--

DROP TABLE IF EXISTS `interact_comment`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `interact_comment` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `user_name` varchar(20) NOT NULL,
  `target` varchar(20) NOT NULL,
  `content` longtext NOT NULL,
  `type` varchar(20) NOT NULL,
  `dislike` int NOT NULL,
  `like` int NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=31 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `interact_comment`
--

LOCK TABLES `interact_comment` WRITE;
/*!40000 ALTER TABLE `interact_comment` DISABLE KEYS */;
INSERT INTO `interact_comment` VALUES (23,'jing','67','桀桀桀','创作',0,0),(24,'没有问题','72','jing是猴猴，所以猴猴是猴猴','创作',1,0),(25,'jing','64','你好啊','创作',1,0),(26,'星期五','64','巴拉巴拉','创作',0,0),(27,'jing','64','确实','创作',0,0),(28,'jing','75','好哇','创作',0,0),(29,'星期六','64','巴拉巴拉','创作',0,0),(30,'jing','77','你好 ','创作',0,0);
/*!40000 ALTER TABLE `interact_comment` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `interact_concen`
--

DROP TABLE IF EXISTS `interact_concen`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `interact_concen` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `user_name` varchar(20) NOT NULL,
  `target` varchar(20) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=34 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `interact_concen`
--

LOCK TABLES `interact_concen` WRITE;
/*!40000 ALTER TABLE `interact_concen` DISABLE KEYS */;
INSERT INTO `interact_concen` VALUES (28,'1','1'),(29,'Lu','Lu'),(30,'星期五','1'),(31,'jing','1'),(32,'星期六','Lu'),(33,'jing','jing');
/*!40000 ALTER TABLE `interact_concen` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `interact_creation`
--

DROP TABLE IF EXISTS `interact_creation`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `interact_creation` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `user_name` varchar(20) NOT NULL,
  `introd_cont` longtext NOT NULL,
  `content` longtext NOT NULL,
  `is_punish` varchar(10) NOT NULL,
  `creation_id` int NOT NULL,
  `title` longtext NOT NULL DEFAULT (_utf8mb3''),
  `comment` int NOT NULL,
  `dislike` int NOT NULL,
  `like` int NOT NULL,
  `look` int NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=78 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `interact_creation`
--

LOCK TABLES `interact_creation` WRITE;
/*!40000 ALTER TABLE `interact_creation` DISABLE KEYS */;
INSERT INTO `interact_creation` VALUES (62,'1','很强','第一篇博客\r\n','已发布',1,'1',0,1,1,3),(63,'Lu','','','已发布',1,'',0,0,1,5),(64,'1','这是一门由同济大学好老师开展的一门计算机专业基础课程','郝老师水平可是很高的\r\n','已发布',2,'计算机组成原理',4,1,4,17),(66,'Lu','','','未发布',2,'',0,0,0,1),(67,'Lu','1号','红红火火恍恍惚惚哈哈哈急急急寄','已发布',3,'发电1号',1,1,3,7),(70,'没有问题','jing是猴猴','','已发布',2,'jing！',0,0,0,1),(71,'没有问题','','','未发布',2,'',0,0,0,0),(75,'jing','123hhhh','123','已发布',1,'hello',1,0,0,5),(76,'星期六','汇报','汇报1111','已发布',1,'作业汇报',0,0,1,1);
/*!40000 ALTER TABLE `interact_creation` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `interact_dislike`
--

DROP TABLE IF EXISTS `interact_dislike`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `interact_dislike` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `user_name` varchar(20) NOT NULL,
  `target` varchar(20) NOT NULL,
  `type` varchar(20) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=47 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `interact_dislike`
--

LOCK TABLES `interact_dislike` WRITE;
/*!40000 ALTER TABLE `interact_dislike` DISABLE KEYS */;
INSERT INTO `interact_dislike` VALUES (41,'1','61','创作'),(42,'1','62','创作'),(44,'jing','64','创作'),(45,'星期六','67','创作'),(46,'jing','77','创作');
/*!40000 ALTER TABLE `interact_dislike` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `interact_like`
--

DROP TABLE IF EXISTS `interact_like`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `interact_like` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `user_name` varchar(20) NOT NULL,
  `target` varchar(20) NOT NULL,
  `type` varchar(20) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=99 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `interact_like`
--

LOCK TABLES `interact_like` WRITE;
/*!40000 ALTER TABLE `interact_like` DISABLE KEYS */;
INSERT INTO `interact_like` VALUES (83,'1','61','创作'),(84,'1','62','创作'),(85,'1','64','创作'),(86,'1','65','创作'),(87,'1','63','创作'),(88,'1','67','创作'),(89,'jing','67','创作'),(93,'星期五','64','创作'),(94,'jing','64','创作'),(95,'星期六','67','创作'),(96,'星期六','64','创作'),(97,'星期六','76','创作'),(98,'jing','77','创作');
/*!40000 ALTER TABLE `interact_like` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `interact_message`
--

DROP TABLE IF EXISTS `interact_message`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `interact_message` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `target` varchar(20) NOT NULL,
  `content` longtext NOT NULL,
  `is_read` varchar(10) NOT NULL,
  `type` varchar(10) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=47 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `interact_message`
--

LOCK TABLES `interact_message` WRITE;
/*!40000 ALTER TABLE `interact_message` DISABLE KEYS */;
INSERT INTO `interact_message` VALUES (19,'5','1 赞了你的博客 《111》 ','未读','like'),(20,'5','1 赞了你的博客 《1》 ','未读','like'),(22,'5','1 赞了你的博客 《计算机组成原理》 ','未读','like'),(23,'5','1 赞了你的博客 《zcr的高级博客》 ','未读','like'),(24,'6','1 赞了你的博客 《》 ','未读','like'),(25,'6','1 赞了你的博客 《发电1号》 ','未读','like'),(26,'6','jing 赞了你的博客 《发电1号》 ','未读','like'),(27,'6','jing 评论了你的博客 《发电1号》 :桀桀桀','未读','comment'),(28,'4','没有问题 评论了你的博客 《猴猴》 :jing是猴猴，所以猴猴是猴猴','未读','comment'),(29,'5','jing 评论了你的博客 《计算机组成原理》 :你好啊','未读','comment'),(30,'5','星期五 赞了你的博客 《计算机组成原理》 ','未读','like'),(31,'5','星期五 赞了你的博客 《计算机组成原理》 ','未读','like'),(32,'5','星期五 赞了你的博客 《计算机组成原理》 ','未读','like'),(33,'5','星期五 赞了你的博客 《计算机组成原理》 ','未读','like'),(34,'4','星期五 举报了 1 的编号为64的博客: 写的太好了','未读','report'),(35,'5','星期五 评论了你的博客 《计算机组成原理》 :巴拉巴拉','未读','comment'),(36,'5','jing 赞了你的博客 《计算机组成原理》 ','未读','like'),(37,'5','jing 评论了你的博客 《计算机组成原理》 :确实','未读','comment'),(38,'4','jing 评论了你的博客 《hello》 :好哇','未读','comment'),(39,'4','jing 举报了 1 的编号为64的博客: 写的好','未读','report'),(40,'6','星期六 赞了你的博客 《发电1号》 ','未读','like'),(41,'5','星期六 赞了你的博客 《计算机组成原理》 ','未读','like'),(42,'5','星期六 评论了你的博客 《计算机组成原理》 :巴拉巴拉','未读','comment'),(43,'4','星期六 举报了 星期六 的编号为76的博客: 举报','未读','report'),(44,'9','星期六 赞了你的博客 《作业汇报》 ','未读','like'),(45,'4','jing 赞了你的博客 《123》 ','未读','like'),(46,'4','jing 评论了你的博客 《123》 :你好 ','未读','comment');
/*!40000 ALTER TABLE `interact_message` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `interact_refer`
--

DROP TABLE IF EXISTS `interact_refer`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `interact_refer` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `echo_id` varchar(20) NOT NULL,
  `refer_id` varchar(20) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `interact_refer`
--

LOCK TABLES `interact_refer` WRITE;
/*!40000 ALTER TABLE `interact_refer` DISABLE KEYS */;
/*!40000 ALTER TABLE `interact_refer` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `reg_log_users`
--

DROP TABLE IF EXISTS `reg_log_users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `reg_log_users` (
  `id` bigint NOT NULL AUTO_INCREMENT,
  `user_name` varchar(20) NOT NULL,
  `user_password` varchar(100) NOT NULL,
  `user_email` varchar(254) NOT NULL,
  `favor_movie` varchar(100) NOT NULL,
  `favor_novel` varchar(100) NOT NULL,
  `favor_song` varchar(100) NOT NULL,
  `admin_right` varchar(4) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `reg_log_users`
--

LOCK TABLES `reg_log_users` WRITE;
/*!40000 ALTER TABLE `reg_log_users` DISABLE KEYS */;
INSERT INTO `reg_log_users` VALUES (6,'jing','cr20032698','zcr2152809@gmail.com','蜘蛛侠','蜘蛛侠','蜘蛛侠','0001'),(7,'1','0Poiuytrewq','2390754326@qq.com','111','111','111','0000'),(8,'Lu','Lu123456','1@qq.com','哈哈哈','计算机组成原理','只因你太美','0000'),(9,'没有问题','hx123456','zz206290996@163.com','大空头','树上的男爵','不要告别','0000'),(10,'星期五','xingqiwu','xingqiwu@tongji.edu.cn','星期五','星期五','星期五','1111'),(11,'星期六','xingqiliu','xingqiliu@gmail.com','1234','1234','1234','0000');
/*!40000 ALTER TABLE `reg_log_users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-06-28 19:02:48
