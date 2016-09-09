create table student (
		sno char(8),
		sname char(16) unique,
		sage int,
		sgender char(1),
		primary key (sno)
);

create table student2 (
	
		id int,
	
	name char(16) unique,
	
	score float,

		primary key(id)
 
);




execfile studentInsertQueries.sql;



execfile student2InsertQueries.sql;

select * from student;
select * from student2;

select * from student where sno = '00000970';
select * from student where sage <= 980 and sgender='F'; 

create index snameIndex on student2(sname);

select * from student2 where sname = 'name1000'; 

insert into student2 values(1080101010,'name1010',74.5);
select from student2 where sname = 'name1010'; 

delete from student2 where sname = 'name1010'; 
select * from student2 where sname = 'name1010';

drop index snameIndex;
select * from student2 where sname = 'name1000';

//删除记录with条件
delete from student2 where sname = 'name1000';

//删除全部记录
delete from student2;

//删除表
drop table student2;


//退出
quit;
