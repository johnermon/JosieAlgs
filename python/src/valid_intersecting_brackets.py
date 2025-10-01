def valid_intersecting_brackets(input:str) -> bool:
    stack:list[str] = []
    for char in input:
        if char in  ('(' , '{', '[', '<'):
            stack.append(char)
            continue
        
        #im glad after 20 years python made match cases, thats cool ig
        open:str
        match char:
            case ')':
                open = '('
            case '}':
                open = '{'
            case ']':
                open = '['
            case '>':
                open = '<'
            case _:
                continue

        countinue_outer = False
        for i, curr in enumerate(stack):
            if open == curr:
                countinue_outer = True
                stack.pop(i)
                break

        #to those who say that a flag and a branch are more ideomatic in this case than a single
        #bracket, i say no you are wrong srry, unstructured control flow works better here
        if countinue_outer:
            continue

        return False

    #the idea of "truthy" values hurts my head
    return not bool(stack)


                
