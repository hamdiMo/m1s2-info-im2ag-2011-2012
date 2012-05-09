create or replace trigger trigger1
       before update or delete on LesTickets
       for each row
declare
	nbPlaces integer := 0;
begin
	--if datediff(day,:NEW.dateEmission,:NEW.dateRep) > 1 then 
	if days(:NEW.dateEmission) + 1 < days(:NEW.dateRep) then  
		select count(*) into nbPlaces
		from LesPlaces
		where (noPlace,noRang) not in (select (noPlace,noRang) from LesTickets);
		if nbPlaces <= 70 then
		    raise_application_error(-20001, 'nombre places restantes < 70 && -1 jour avant representation'); 
		end if;
	end if;
end;
/