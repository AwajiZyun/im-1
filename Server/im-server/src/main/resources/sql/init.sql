-- zh2683 2018-10-28 用户表
drop table if exists user;
create table user(
  id varchar(32) not null,
  code varchar(20) unique not null,
  email varchar(50) unique not null,
  email_crc32 bigint not null,
  nickname varchar(20) not null,
  password varchar(32) not null,
  sex int not null,
  `delete` int not null,
  createTime datetime not null,
  modifyTime datetime,
  primary key(id)
) engine=innodb;

alter table user add index i_email_crc32(email_crc32);

-- zh2683 2018-12-24 好友关系表
drop table if exists friends;
create table friends(
  id varchar(32) not null,
  userCode varchar(20) not null,
  friendCode varchar(20) not null,
  createTime datetime not null,
  unique index ui_uc_fc(userCode, friendCode),
  index i_fc(friendCode)
) engine=innodb;